#ifndef _BOOTLOADEX_ARK_H_
#define _BOOTLOADEX_ARK_H_

#include <systemctrl_ark.h>
#include <rebootexconfig.h>

typedef struct{
    u8 filesize[4];
    char namelen;
    char name[1];
} ArkFlashFile;

// ARK specific functions
void initArkRebootConfig(BootLoadExConfig*);
int UnpackBootConfigArkPSP(char *buffer, int length);
int findArkFlashFile(BootFile* file, const char* path);

#endif
