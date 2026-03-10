#include <string.h>

#include <psptypes.h>

#include <idstorage_ms.h>
#include <sysreg.h>
#include <systemctrl_ark.h>

extern key_entry *key_entries;
extern char *hex64(unsigned long long v);
extern int read_ms_leaf(void *buf, leaf_entry *leaf);
extern int _sceIdStorageLock(void);
extern int _sceIdStorageUnlock(void);

char *_sceIdStorageGetMsFilePath(char *dest, int remove_drive_prefix)
{
    const char *id_stor_path = ARK_DC_IDSTOR_PATH;

    if (remove_drive_prefix)
        id_stor_path += 4;

    strcpy(dest, id_stor_path);
    strcat(dest, hex64(sysreg_get_fuse_id()));
    strcat(dest, ".bin");

    return dest;
}

int _sceIdStorageFindKeyPos(u16 key, leaf_entry *leaf)
{
    for (int i = 0; i < MAX_LEAFS; i++)
    {
        key_entry entry = key_entries[i];
        if (entry.key == key)
        {
            leaf->key = entry.key;
            leaf->offset = entry.offset;
            leaf->len = key_entries[i + 1].offset - leaf->offset;
            
            return 0;
        }
        else if (entry.key == END_KEY)
        {
            return SCE_ERROR_NOT_FOUND;
        }
    }

    return SCE_ERROR_NOT_FOUND;
}

int sceIdStorageReadLeaf(u16 key, void *buf)
{
    int res;
    leaf_entry leaf;

    if (key > 0xffef)
        return SCE_ERROR_INVALID_ID;

    if ((res = _sceIdStorageLock()) < 0)
        return res;

    if ((res = _sceIdStorageFindKeyPos(key, &leaf)) < 0)
        goto exit;

    if (leaf.len < LEAF_SIZE)
        memset(buf, 0, LEAF_SIZE);

    if (read_ms_leaf(buf, &leaf) != leaf.len)
    {
        return SCE_ERROR_KERNEL_FILE_READ_ERROR;
    }

exit:
    _sceIdStorageUnlock();

    return res;
}

int sceIdStorageLookup(u16 key, int offset, void *buf, u32 len)
{
    u8 tmpBuf[LEAF_SIZE];
    int res;

    if (key >= MAX_KEY)
        return SCE_ERROR_INVALID_ID;

    if (offset + len > LEAF_SIZE)
        return SCE_ERROR_INVALID_ARGUMENT;

    if ((res = _sceIdStorageLock()) < 0)
        return res;

    if (len == LEAF_SIZE)
        res = sceIdStorageReadLeaf(key, buf);
    else
    {
        res = sceIdStorageReadLeaf(key, tmpBuf);

        if (res == 0)
            memcpy(buf, (const void *)(&tmpBuf[offset]), len);
    }

    _sceIdStorageUnlock();

    return res;
}