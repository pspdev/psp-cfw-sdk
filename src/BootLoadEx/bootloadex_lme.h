#ifndef BOOTLOADEX_LME_H
#define BOOTLOADEX_LME_H

extern int lme_recovery_mode;

void xor_cipher(u8* data, u32 size, u8* key, u32 key_size);
int LMEPRXDecrypt(PSP_Header* prx, unsigned int size, unsigned int * newsize);
int LMECheckExec(unsigned char * addr, void * arg2);

void BtcnfPathHandlerLME(char* path);
int UnpackBootConfigLMEPSP(char *buffer, int length);

#endif