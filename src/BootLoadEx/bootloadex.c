/*
 * This file is part of PRO CFW.

 * PRO CFW is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * PRO CFW is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PRO CFW. If not, see <http://www.gnu.org/licenses/ .
 */

#include <string.h>
#include <pspextratypes.h>

#include <cfwmacros.h>
#include <systemctrl.h>
#include <systemctrl_se.h>
#include <bootloadex.h>
#include <rebootexconfig.h>
#include <systemctrl_ark.h>


int psp_model = PSP_1000;
u32 reboot_end = REBOOT_TEXT+0x20000; // 128KB at most
u32 loadcore_text = 0;
BootLoadExConfig* ble_config;
BootFileList* boot_files = (BootFileList*)BOOT_FILE_LIST_ADDR;

// sceBoot Main Function
int (* sceBoot)(int, int, int, int, int, int, int) = (void *)(REBOOT_TEXT);

// Instruction Cache Invalidator
void (* sceBootIcacheInvalidateAll)(void) = NULL;

// Data Cache Invalidator
void (* sceBootDacheWritebackInvalidateAll)(void) = NULL;

// Sony PRX Decrypter Function Pointer
int (* origPRXDecrypt)(void *, unsigned int, unsigned int *) = NULL;
int (* origCheckExecFile)(unsigned char * addr, void * arg2) = NULL;

// UnpackBootConfig
int (* UnpackBootConfig)(char * buffer, int length) = NULL;
u32 UnpackBootConfigCall = 0;
u32 UnpackBootConfigArg = 0;

// rtm module flag
int rebootmodule_open = 0;


// Invalidate Instruction and Data Cache
void flushCache(void)
{
    // Invalidate Data Cache
    sceBootDacheWritebackInvalidateAll();
    // Invalidate Instruction Cache
    sceBootIcacheInvalidateAll();
}

// Custom PRX Support
int PRXDecryptPatched(PSPHeader* prx, unsigned int size, unsigned int * newsize)
{
    // Custom Packed PRX File
    if ( (_lb((u32)prx + 0x150) == 0x1F && _lb((u32)prx + 0x151) == 0x8B) // GZIP
            || prx->oe_tag == OE_TAG_PRO // PRO-type PRX
            || prx->oe_tag == OE_TAG_LME // ME-type PRX
    ){

        if (ble_config->extraPRXDecrypt){ // decrypt ME firmware file
            ble_config->extraPRXDecrypt(prx, size, newsize);
        }

        // Read GZIP Size
        *newsize = prx->comp_size;
        
        // Remove PRX Header
        memcpy(prx, (u8*)prx + 0x150, prx->comp_size);
        
        // Fake Decrypt Success
        return 0;
    }
    
    // Decrypt Sony PRX Files
    return origPRXDecrypt(prx, size, newsize);
}


int CheckExecFilePatched(unsigned char * addr, void * arg2)
{
    if (ble_config->boot_storage == FLASH_BOOT){
        //scan structure
        //6.31 kernel modules use type 3 PRX... 0xd4~0x10C is zero padded
        int pos = 0; for(; pos < 0x38; pos++)
        {
            //nonzero byte encountered
            if(addr[pos + 212])
            {
                //forward to unsign function?
                return origCheckExecFile(addr, arg2);
            }
        }
    }

    if (ble_config->extraCheckExecFile){
        ble_config->extraCheckExecFile(addr, arg2);
    }

    //return success
    return 0;
}

void unPatchLoadCorePRXDecrypt(){
    u32 decrypt_call = JAL(PRXDecryptPatched);
    u32 text_addr = loadcore_text;
    u32 top_addr = text_addr+0x8000;

    for (u32 addr = text_addr; addr<top_addr; addr+=4) {
        if (_lw(addr) == decrypt_call){
            _sw(JAL(origPRXDecrypt), addr);
        }
    }

}

void unPatchLoadCoreCheckExec(){
    u32 check_call = JAL(CheckExecFilePatched);
    u32 text_addr = loadcore_text;
    u32 top_addr = text_addr+0x8000;

    for (u32 addr = text_addr; addr<top_addr; addr+=4) {
        if (_lw(addr) == check_call){
            _sw(JAL(origCheckExecFile), addr);
        }
    }

}

void patchLoadCore(u32 module_start){

    // Calculate Text Address and size
    u32 text_addr = module_start-0xAF8; // this calculation is exact, but due to dynamic patching it doesn't matter anymore
    u32 top_addr = text_addr+0x8000; // read 32KB at most (more than enough to scan loadcore)
    
    // Fetch Original Decrypt Function Stub
    origPRXDecrypt = (void *)FindImportRange("memlmd", 0xEF73E85B, text_addr, top_addr);
    origCheckExecFile = (void *)FindImportRange("memlmd", 0x6192F715, text_addr, top_addr);

    u32 decrypt_call = JAL(origPRXDecrypt);
    u32 check_call = JAL(origCheckExecFile);

    int devkit_patched = 0;

    // Hook Signcheck Function Calls
    for (u32 addr = text_addr; addr<top_addr; addr+=4){
        u32 data = _lw(addr);
        if (data == decrypt_call){
            _sw(JAL(PRXDecryptPatched), addr);
        }
        else if (data == check_call){
            _sw(JAL(CheckExecFilePatched), addr);
        }
        else if (!devkit_patched && data == 0x24040015){
            // Don't break on unresolved syscalls
            u32 a = addr;
            do { a-=4; } while (_lw(a) != 0x27BD0030);
            _sw(0x00001021, a+4);
            devkit_patched = 1;
        }
    }
    
    loadcore_text = text_addr;
    flushCache();
}

// Common rebootex patches for PSP and Vita
void findBootFunctions(){
    // find functions
    for (u32 addr = REBOOT_TEXT; addr<reboot_end; addr+=4){
        u32 data = _lw(addr);
        if (data == 0xBD01FFC0){ // sceBootDacheWritebackInvalidateAll
            u32 a = addr;
            do {a-=4;} while (_lw(a) != 0x40088000);
            sceBootDacheWritebackInvalidateAll = (void*)a;
        }
        else if (data == 0xBD14FFC0){ // sceBootIcacheInvalidateAll
            u32 a = addr;
            do {a-=4;} while (_lw(a) != 0x40088000);
            sceBootIcacheInvalidateAll = (void*)a;
        }
        else if (strcmp("ApplyPspRelSection", (char*)addr) == 0 || strcmp("StopBoot", (char*)addr) == 0){
            reboot_end = (addr & -0x4); // found end of reboot buffer
            break;
        }
        else {
            if (ble_config->boot_type == TYPE_REBOOTEX){
                if (data == 0x8FA50008 && _lw(addr+8) == 0x8FA40004){ // UnpackBootConfig
                    UnpackBootConfigArg = addr+8;
                    u32 a = addr;
                    do { a+=4; } while (_lw(a) != 0x24060001);
                    UnpackBootConfig = (void*)K_EXTRACT_CALL(a-4);
                    UnpackBootConfigCall = a-4;
                }
            }
            else if (ble_config->boot_type == TYPE_PAYLOADEX){
                if (data == 0x8FA40004){ // UnpackBootConfig
                    if (_lw(addr+8) == 0x8FA50008) {
                        UnpackBootConfigArg = addr;
                        UnpackBootConfig = (void*)K_EXTRACT_CALL(addr+4);
                        UnpackBootConfigCall = addr+4;
                    }
                    else if (_lw(addr+4) == 0x8FA50008) {
                        UnpackBootConfigArg = addr;
                        UnpackBootConfig = (void*)K_EXTRACT_CALL(addr+8);
                        UnpackBootConfigCall = addr+8;
                    }
                }
            }
        }
    }
    flushCache();
}

void configureBoot(BootLoadExConfig* config){
    ble_config = config;
}
