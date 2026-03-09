#ifndef __FAT_H__
#define __FAT_H__

#define FAT_TYPE_12    0
#define FAT_TYPE_16    1
#define FAT_TYPE_32    2

#define FAT_ATTR_READ_ONLY      0x01
#define FAT_ATTR_HIDDEN         0x02
#define FAT_ATTR_SYSTEM         0x04
#define FAT_ATTR_VOLUME_ID      0x08
#define FAT_ATTR_DIRECTORY      0x10
#define FAT_ATTR_ARCHIVE        0x20
#define FAT_ATTR_LONG_NAME      FAT_ATTR_READ_ONLY | FAT_ATTR_HIDDEN | FAT_ATTR_SYSTEM | FAT_ATTR_VOLUME_ID

#define SEEK_SET    0
#define SEEK_CUR    1
#define SEEK_END    2

typedef struct
{
    u8  attributes;
    u32 size;
    u32 start_cluster;
    u32 cur_cluster;
    u32 cur_sector; // Sector offset within the current cluster
    u32 cur_sector_offset; // Byte offset within the current sector
    u32 cur_offset; // Absolute byte offset within the file
} MsFatFile;

int MsFatMount();
int MsFatReadLogicalSector();
u32 MsFatGetNextCluster(u32 cluster);
int MsFatIsValidCluster(u32 cluster);
int MsFatFindFile(u32 dir_cluster, char *filename, int rootcase, MsFatFile *file);
int MsFatOpen(const char *path);
int MsFatSeek(u32 offset, int whence);
int MsFatRead(void *buf, u32 size);
int MsFatClose();


#endif


