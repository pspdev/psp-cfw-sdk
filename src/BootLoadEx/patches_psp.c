#include <string.h>

#include <systemctrl_ark.h>
#include <cfwmacros.h>
#include <systemctrl.h>
#include <systemctrl_se.h>
#include <bootloadex.h>
#include <pspbtcnf.h>


// Time Machine module
#define PATH_TMCTRL FLASH0_PATH "tmctrl.prx"

//io functions
int (* sceBootLfatOpen)(const char * filename) = NULL;
int (* sceBootLfatRead)(char * buffer, int length) = NULL;
int (* sceBootLfatClose)(void) = NULL;


int file_exists(const char *path)
{
    int ret;

    if (ble_config->boot_storage == MS_BOOT)
        ret = ble_config->extra_io.psp_io.FatOpen(path);
    else
        ret = sceBootLfatOpen(path);

    if (ret >= 0) {
        if (ble_config->boot_storage == MS_BOOT)
            ble_config->extra_io.psp_io.FatClose();
        else
            sceBootLfatClose();
        return 1;
    }

    return 0;
}

int loadcoreModuleStartPSP(void * arg1, void * arg2, void * arg3, int (* start)(void *, void *, void *)){
    patchLoadCore((u32)start);
    return start(arg1, arg2, arg3);
}

int is_fatms371(void)
{
    return file_exists(PATH_FATMS_HELPER + sizeof("flash0:") - 1) && file_exists(PATH_FATMS_371 + sizeof("flash0:") - 1);
}

int patch_bootconf_fatms371(char *buffer, int length)
{
    int newsize;
    int result = length;

    newsize = AddPRX(buffer, "/kd/fatms.prx", PATH_FATMS_HELPER+sizeof(FLASH0_PATH)-2, 0xEF & ~VSH_RUNLEVEL);
    if (newsize > 0) result = newsize;

    RemovePrx(buffer, "/kd/fatms.prx", 0xEF & ~VSH_RUNLEVEL);
    
    newsize = AddPRX(buffer, "/kd/wlan.prx", PATH_FATMS_371+sizeof(FLASH0_PATH)-2, 0xEF & ~VSH_RUNLEVEL);
    if (newsize > 0) result = newsize;

    return result;
}

int patch_bootconf_timemachine(char *buffer, int length)
{
    int newsize;
    int result = length;

    // Insert tmctrl
    newsize = AddPRX(buffer, "/kd/lfatfs.prx", PATH_TMCTRL+sizeof(FLASH0_PATH)-2, 0x000000EF);
    if (newsize > 0) result = newsize;

    // Remove lfatfs
    newsize = RemovePrx(buffer, "/kd/lfatfs.prx", 0x000000EF);
    if (newsize > 0) result = newsize;

    return result;
}

// IO Patches
int _sceBootLfatMount()
{
    return ble_config->extra_io.psp_io.FatMount();
}

int _sceBootLfatOpen(char * filename)
{
    int is_btcnf = (memcmp(filename+4, "pspbtcnf", 8) == 0);
    
    if (is_btcnf){
        boot_files->nfiles = 0;
        if (filename[12] == '_'){
            psp_model = (10*(filename[13]-'0') + (filename[14]-'0')) - 1;
        }
        if (ble_config->extra_io.psp_io.BtcnfPathHandler){
            ble_config->extra_io.psp_io.BtcnfPathHandler(filename);
        }
    }

    // add file to boot list
    strcpy((char*)&(boot_files->bootfile[boot_files->nfiles++]), filename);

    //load on reboot module open
    if (strcmp(filename, REBOOT_MODULE) == 0)
    {
        //mark for read
        rebootmodule_open = 1;

        //return success
        return 0;
    }

    if (ble_config->boot_storage == MS_BOOT){
        char path[128];
        strcpy(path, ble_config->extra_io.psp_io.tm_path);
        strcat(path, filename);
        if (is_btcnf && ble_config->boot_type == TYPE_PAYLOADEX){
            memcpy(&path[strlen(path) - 4], "_dc.bin", 8);
        }
        return ble_config->extra_io.psp_io.FatOpen(path);
    }
    else {
        // patch to allow custom boot
        if (is_btcnf){
            int res = -1;
            // check for custom btcnf
            filename[6] = 't'; // pstbtcnf.bin
            res = sceBootLfatOpen(filename);
            if (res >= 0) return res;
            filename[6] = 'p'; // fallback
        }
        //forward to original function
        return sceBootLfatOpen(filename);
    }
}

int _sceBootLfatRead(char * buffer, int length)
{
    //load on reboot module
    if (rebootmodule_open)
    {
        //copy load on reboot module
        int min = ble_config->rtm_mod.size < length ? ble_config->rtm_mod.size : length;
        if (min > 0){
            memcpy(buffer, ble_config->rtm_mod.buffer, min);
            ble_config->rtm_mod.buffer += min;
            ble_config->rtm_mod.size -= min;
        }

        //set filesize
        return min;
    }

    if (ble_config->boot_storage == MS_BOOT)
        return ble_config->extra_io.psp_io.FatRead(buffer, length);
    
    //forward to original function
    return sceBootLfatRead(buffer, length);
}

int _sceBootLfatClose(void)
{
    //reboot module close
    if (rebootmodule_open)
    {
        //mark as closed
        rebootmodule_open = 0;
        ble_config->rtm_mod.buffer = NULL;
        ble_config->rtm_mod.size = 0;

        //return success
        return 0;
    }

    if (ble_config->boot_storage == MS_BOOT)
        return ble_config->extra_io.psp_io.FatClose();
    
    //forward to original function
    return sceBootLfatClose();
}

int UnpackBootConfigPSP(char **p_buffer, int length){

    int result = length;
    int newsize;
    char *buffer = (void*)BOOTCONFIG_TEMP_BUFFER;

    result = (*UnpackBootConfig)(*p_buffer, length);
    memcpy(buffer, *p_buffer, length);
    *p_buffer = buffer;

    if (ble_config->UnpackBootConfig){
        newsize = ble_config->UnpackBootConfig(buffer, length);
        if (newsize > 0) result = newsize;
    }

    //reboot variable set
    if (ble_config->boot_type == TYPE_REBOOTEX && ble_config->rtm_mod.before && ble_config->rtm_mod.buffer && ble_config->rtm_mod.size)
    {
        //add reboot prx entry
        newsize = AddPRX(buffer, ble_config->rtm_mod.before, REBOOT_MODULE, ble_config->rtm_mod.flags);
        if (newsize > 0) result = newsize;
    }

    if (ble_config->extra_io.psp_io.use_fatms371 && is_fatms371())
    {
        newsize = patch_bootconf_fatms371(buffer, length);
        if (newsize > 0) result = newsize;
    }

    if (ble_config->boot_storage == MS_BOOT){
        newsize = patch_bootconf_timemachine(buffer, length);
        if (newsize > 0) result = newsize;
    }

    return result;
}

// patch boot on psp
void patchBootPSP(){

    _sw(0x27A40004, UnpackBootConfigArg); // addiu $a0, $sp, 4
    _sw(JAL(UnpackBootConfigPSP), UnpackBootConfigCall); // Hook UnpackBootConfig

    // make sure we read as little ram as possible
    int patches = (ble_config->boot_storage == MS_BOOT)? 10:9;
    
    for (u32 addr = REBOOT_TEXT; addr<reboot_end && patches; addr+=4){
        u32 data = _lw(addr);
        if (data == 0x8E840000 || data == 0x8EA40000){ // FatOpen
            if (ble_config->boot_storage == MS_BOOT){
                int found = 0;
                for (int i=8; !found; i+=4) {
                    if (IS_JAL(_lw(addr-i))) { // FatMount
                        _sw(JAL(_sceBootLfatMount), addr-i);
                        found = 1;
                    }
                }
            }
            sceBootLfatOpen = (void*)K_EXTRACT_CALL(addr-4);
            _sw(JAL(_sceBootLfatOpen), addr-4);
            patches--;
        }
        else if ((data == _lw(addr+4)) && (data & 0xFC000000) == 0xAC000000){ // Patch ~PSP header check
            // Returns size of the buffer on loading whatever modules
            _sw(0xAFA50000, addr+4); // sw a1, 0(sp)
            _sw(0x20A30000, addr+8); // move v1, a1
            patches--;
            addr += 8;
        }
        else if (data == 0xAE840004 || data == 0xAEA30004){ // FatRead
            addr += 4;
            while (!IS_JAL(_lw(addr))) { addr += 4; }
            sceBootLfatRead = (void*)K_EXTRACT_CALL(addr);
            _sw(JAL(_sceBootLfatRead), addr);
            patches--;
        }
        else if (data == 0xAE930008 || data == 0xAEB40008){ // FatClose
            sceBootLfatClose = (void*)K_EXTRACT_CALL(addr-4);
            _sw(JAL(_sceBootLfatClose), addr-4);
            patches--;
        }
        else if (data == 0x02A0E821 || data == 0x0280E821){ // found loadcore jump on PSP
            _sw(0x3821 | ((_lw(addr-4) & 0x3E00000) >> 5), addr-4); // ADDU $a3 $zero <reg>
            _sw(JUMP(loadcoreModuleStartPSP), addr);
            _sw(data, addr + 4);
            patches--;
            addr += 4;
        }
        else if (data == 0x2C860040 || data == 0x2C850040){ // kdebug patch
            _sw(0x03E00008, addr-4); // make it return 1
            _sw(0x24020001, addr); // rebootexcheck1
            patches--;
        }
        else if (data == 0x24D90001 || data == 0x256A0001){  // rebootexcheck5
            u32 a = addr;
            u32 insMask;
            do {
                a-=4;
                insMask = _lw(a) & 0xFFFF0000;
            } while (insMask != 0x04400000 && insMask != 0x04420000);
            _sw(NOP, a); // Killing Branch Check bltz/bltzl ...
            patches--;
        }
        else if (data == 0x27BDFFE0 && _lw(addr+4) == 0x3C028861 && ble_config->boot_storage == MS_BOOT) { // nand enc
            MAKE_DUMMY_FUNCTION_RETURN_0(addr);
            patches--;
        }
        else {
            if (ble_config->boot_type == TYPE_REBOOTEX){
                if (data == 0x34650001){ // rebootexcheck2
                    _sw(NOP, addr-4); // Killing Branch Check bltz ...
                    patches--;
                }
                else if (data == 0x00903021 && _lw(addr+4) == 0x00D6282B){ // rebootexcheck3 and rebootexcheck4
                    u32 a = addr;
                    do {a-=4;} while (_lw(a) != NOP);
                    _sw(NOP, a-4); // Killing Branch Check beqz
                    _sw(NOP, addr+8); // Killing Branch Check bltz ...
                    patches--;
                }
            }
            else if (ble_config->boot_type == TYPE_PAYLOADEX){
                if (data == 0x25AC003F){ // payloadexcheck2
                    _sw(NOP, addr-44); // Killing Branch Check bltz ...
                    patches--;
                }
                else if (data == 0x01F7702B){ // rebootexcheck3 and rebootexcheck4
                    _sw(NOP, addr-12); // Killing Branch Check bltz
                    _sw(NOP, addr+4); // Killing Branch Check beqz ...
                    patches--;
                }
            }
        }
    }

    // Flush Cache
    flushCache();
}
