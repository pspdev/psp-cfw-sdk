#ifndef __IDSTORAGE_MS_H__
#define __IDSTORAGE_MS_H__

#define LEAF_SIZE 0x200
#define MAX_LEAFS 0x1E0
#define MAX_KEY 0xFFF0
#define END_KEY 0xFFFF

#define SCE_ERROR_NOT_SUPPORTED           0x80000004
#define SCE_ERROR_NOT_FOUND               0x80000025
#define SCE_ERROR_INVALID_ID              0x80000100
#define SCE_ERROR_KERNEL_FILE_READ_ERROR  0x80020130
#define SCE_ERROR_INVALID_ARGUMENT        0x800001FF

typedef struct {
    u16 key;
    u16 offset;
    u16 len;
} leaf_entry;

typedef struct {
    u16 key;
    u16 offset;
} key_entry;

char *_sceIdStorageGetMsFilePath(char *dest, int remove_drive_prefix);
int sceIdStorageLookup(u16 key, int offset, void *buf, u32 len);

#endif