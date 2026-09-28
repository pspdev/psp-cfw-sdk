#include <string.h>

#include <pspheaders.h>
#include <systemctrl_ark.h>
#include <cfwmacros.h>
#include <systemctrl.h>
#include <systemctrl_se.h>
#include <pspbtcnf.h>
#include <bootloadex.h>
#include <rebootexconfig.h>


void xor_cipher(u8* data, u32 size, u8* key, u32 key_size)
{
    u32 i;

    for (i = 0; i < size; i++)
    {
        data[i] ^= key[i % key_size];
    }
}

int LMEPRXDecrypt(void* buf, unsigned int size, unsigned int * newsize){
    PSP_Header* prx = (PSP_Header*)buf;
    xor_cipher((u8*)buf + 0x150, 0x10, (u8*)(prx->key_data1), 0x10);
    xor_cipher((u8*)buf + 0x150, prx->comp_size, (u8*)(&prx->scheck[0x38]), 0x20);
    unPatchLoadCorePRXDecrypt();
    return 0;
}

int LMECheckExec(unsigned char * addr, void * arg2){
    unPatchLoadCoreCheckExec();
    return 0;
}