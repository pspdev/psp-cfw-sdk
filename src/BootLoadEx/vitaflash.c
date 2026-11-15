#include <string.h>

#include <cfwmacros.h>

#include "bootloadex.h"


int vitaFlashOpenExtra(BootFile* file, const char* path) {
    u32 nfiles = *(u32*)(VITA_FLASH_EXTRA);
    ExtraFlashFile* cur = (ExtraFlashFile*)((size_t)(VITA_FLASH_EXTRA)+4);

    for (int i=0; i<nfiles; i++) {
        size_t filesize = (cur->filesize[0]) + (cur->filesize[1]<<8) + (cur->filesize[2]<<16) + (cur->filesize[3]<<24);
        if (strncmp(path, cur->name, cur->namelen) == 0) {
            file->buffer = (void*)((size_t)(&(cur->name[0])) + cur->namelen);
            file->size = filesize;
            return 0;
        }
        cur = (ExtraFlashFile*)((size_t)(cur)+filesize+cur->namelen+5);
    }
    return -1;
}

void relocateFlashFile(BootFile* file){
    static u8* curbuf = (u8*)PTR_ALIGN_64(VITA_FLASH_EXTRA+MAX_FLASH0_SIZE);
    memcpy((void *)curbuf, file->buffer, file->size);
    file->buffer = (void *)curbuf;
    curbuf += file->size + 64;
    curbuf = PTR_ALIGN_64(curbuf);
}
