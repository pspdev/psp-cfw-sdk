#include <string.h>
#include <pspsysmem_kernel.h>

#include <cfwmacros.h>
#include <bootloadex.h>
#include <pspbtcnf.h>
#include <systemctrl_ark.h>


int (*pspemuLfatOpen)(BootFile* filename, u32 a1, u32 a2, u32 a3, u32 t0) = NULL;
int (*SetMemoryPartitionTable)(void *sysmem_config, SceSysmemPartTable *table) = NULL;

// Load Core module_start Hook
int loadcoreModuleStartVita(unsigned int args, void* argp, int (* start)(SceSize, void *)) {
    patchLoadCore((u32)start);
    return start(args, argp);
}

void relocateFlashFile(BootFile* file){
    static u8* curbuf = (u8*)PTR_ALIGN_64(VITA_FLASH_ARK+MAX_FLASH0_SIZE);
    memcpy((void *)curbuf, file->buffer, file->size);
    file->buffer = (void *)curbuf;
    curbuf += file->size + 64;
    curbuf = PTR_ALIGN_64(curbuf);
}

int _pspemuLfatOpen(BootFile* file, u32 a1, u32 a2, u32 a3, u32 t0)
{

    int is_btcnf = (memcmp(file->name, "pspbtcnf", 8) == 0);

    if (is_btcnf){
        boot_files->nfiles = 0;
    }

    // add file to boot list
    strcpy((char*)&(boot_files->bootfile[boot_files->nfiles++]), file->name);

    if (ble_config->extra_io.vita_io.pspemuLfatOpenExtra(file) == 0){
        return 0;

	} else if (strcmp(file->name, REBOOT_MODULE) == 0){
        file->buffer = ble_config->rtm_mod.buffer;
        file->size = ble_config->rtm_mod.size;
        relocateFlashFile(file);
        ble_config->rtm_mod.buffer = NULL;
        ble_config->rtm_mod.size = 0;
        return 0;
    }

    pspemuLfatOpen(file, a1, a2, a3, t0);
    return 0; //always return 0 to allow boot with unsuccessfully loaded files
}

int UnpackBootConfigVita(char **p_buffer, int length) {

    int result = length;
    int newsize;
    char *buffer;

    result = (*UnpackBootConfig)(*p_buffer, length);
    buffer = (void*)BOOTCONFIG_TEMP_BUFFER;
    memcpy(buffer, *p_buffer, length);
    *p_buffer = buffer;

    if (ble_config->UnpackBootConfig) {
        newsize = ble_config->UnpackBootConfig(buffer, length);
        if (newsize > 0) {
			result = newsize;
		}
    }

    if (ble_config->boot_type == TYPE_REBOOTEX && ble_config->rtm_mod.before && ble_config->rtm_mod.buffer && ble_config->rtm_mod.size) {
        //add reboot prx entry
        newsize = AddPRX(buffer, ble_config->rtm_mod.before, REBOOT_MODULE, ble_config->rtm_mod.flags);
        if (newsize > 0) {
			result = newsize;
		}
    }

    return result;
}

//extra ram through flash0 ramfs on Vita
void SetMemoryPartitionTablePatched(void *sysmem_config, SceSysmemPartTable *table) {
    // Add flash0 ramfs as partition 11, only the first 16MB are safe to use
    SetMemoryPartitionTable(sysmem_config, table);
    table->extVshell.addr = EXTRA_RAM;
    table->extVshell.size = EXTRA_RAM_SIZE/2;
}

int PatchSysMem(void *a0, void *sysmem_config) {
    int (* module_bootstart)(SceSize args, void *sysmem_config) = (void *)VREAD32((u32)a0 + 0x28);
    u32 text_addr = SYSMEM_TEXT;
    u32 top_addr = text_addr+0x14000;
    int patches = 1;
    for (u32 addr = text_addr; addr<top_addr && patches; addr += 4) {
        u32 data = VREAD32(addr);
        if (data == 0x247300FF){
            SetMemoryPartitionTable = (void*)K_EXTRACT_CALL(addr-20);
			MAKE_CALL(addr-20, SetMemoryPartitionTablePatched);
            patches--;
        }
    }

    flushCache();

    return module_bootstart(4, sysmem_config);
}

/*
    0x89FF0000: Apitype
    0x89FF0004: vsh: 2, update: 3, pops: 4, licence: 5, app: 6, umd: 7, mlnapp: 8
    0x89FF0008: Path #1
    0x89FF0048: Path #2
    0x89FF0088: Path #3
    0x89FF00C8: SFO buffer
    0x89FF14C8: 0x000001F4
    0x89FF14CC: 0x000000DC
    0x89FF14D0: 0x00060313
    0x89FF1510: TITLEID
    0x89FF1520: 0x00000003
    0x89FF1540: Path #4
    0x89FF1590: Version
*/
int loadParamsPatched(int a0) {
    int v0 = VREAD32(a0 + 12);
	int v1 = VREAD32(a0 + 16);
	VWRITE32((v1 + (v0 << 5)) - 12, VREAD32(0x89FF0000));
	return 0;
}

// patch reboot on ps vita
void patchBootVita() {

    if (ble_config->boot_type == TYPE_PAYLOADEX){
        *(u32 *)0x89FF0000 = 0x200;
        *(u32 *)0x89FF0004 = 0x2;
    }

    // hijack UnpackBootConfig to insert modules at runtime
	MAKE_INSTRUCTION(UnpackBootConfigArg, 0x27A40004); // addiu $a0, $sp, 4
	MAKE_CALL(UnpackBootConfigCall, UnpackBootConfigVita); // Hook UnpackBootConfig

    int redirect_flash = ble_config->extra_io.vita_io.redirect_flash;

    for (u32 addr = REBOOT_TEXT; addr<reboot_end; addr+=4){
        u32 data = VREAD32(addr);

        if (data == 0xAFBF0000 && VREAD32(addr + 8) == 0x00000000) {
            pspemuLfatOpen = (void *)K_EXTRACT_CALL(addr + 4);
			MAKE_CALL(addr + 4, _pspemuLfatOpen);

		} else if (data == 0x00600008){ // found loadcore jump on Vita
            // Move LoadCore module_start Address into third Argument
			MAKE_INSTRUCTION(addr, 0x00603021); // move a2, v1
            // Hook LoadCore module_start Call
			MAKE_JUMP(addr+8, loadcoreModuleStartVita);

		} else if (data == 0x24040004) {
            if (ble_config->boot_type == TYPE_PAYLOADEX) {
                MAKE_INSTRUCTION(addr, 0x02202021); // move $a0, $s1
                MAKE_CALL(addr - 4, PatchSysMem);
            } else {
                MAKE_INSTRUCTION(addr, 0x02402021); // move $a0, $s2
                MAKE_CALL(addr + 0x64, PatchSysMem);
            }

		} else if ((data & 0x0000FFFF) == 0x8B00 && redirect_flash){
			VWRITE8(addr, 0xA0); // Link Filesystem Buffer to 0x8BA00000

		} else if ((data == VREAD32(addr+4)) && (data & 0xFC000000) == 0xAC000000){ // Patch ~PSP header check
            // Returns zero on loading whatever modules
			MAKE_INSTRUCTION(addr+8, 0x20030000); // move v1, zero

		} else {
            if (ble_config->boot_type == TYPE_PAYLOADEX){
                // Find sceBoot
                if (data == 0x27BD01C0) {
                    sceBoot = (void *)(addr + 4);

				} else if (data == 0x240500CF) {
					// Don't load pspemu params
                    MAKE_CALL(addr + 4, loadParamsPatched);
                }
            }
        }
    }
    // Flush Cache
    flushCache();
}

