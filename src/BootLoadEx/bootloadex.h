#ifndef _BOOTLOADEX_H_
#define _BOOTLOADEX_H_

#include <pspsdk.h>

#include <cfwmacros.h>

#define REBOOT_TEXT (KERNEL_BASE + 0x600000) // reboot.bin load address
#define REBOOTEX_TEXT (KERNEL_BASE + 0xFC0000) // rebootex load address
#define LOADER_TEXT (0x040EC000) // cIPL load address
#define MAINBIN_TEXT (0x04000000) // IPL load address
#define BOOTCONFIG_TEMP_BUFFER 0x88FB0200
#define REBOOT_MODULE "/rtm.prx"

typedef enum {
    FLASH_BOOT,
    MS_BOOT
} BootStorage;

typedef enum {
    TYPE_REBOOTEX,
    TYPE_PAYLOADEX
} BootType;

typedef struct {
    char *name;
    void *buffer;
    u32 size;
} BootFile;

// Sony flash0 files
typedef struct {
    int nfiles;
    char bootfile[100][64]; // list of boot files
} BootFileList;
#define BOOT_FILE_LIST_ADDR 0x08800100

typedef struct
{
    u32 signature;      // 0
    u16 attribute;      // 4  modinfo
    u16 comp_attribute; // 6
    u8 module_ver_lo;   // 8
    u8 module_ver_hi;   // 9
    char modname[28];   // 0A
    u8 version;         // 26
    u8 nsegments;       // 27
    int elf_size;       // 28
    int psp_size;       // 2C
    u32 entry;          // 30
    u32 modinfo_offset; // 34
    int bss_size;       // 38
    u16 seg_align[4];   // 3C
    u32 seg_address[4]; // 44
    int seg_size[4];    // 54
    u32 reserved[5];    // 64
    u32 devkitversion;  // 78
    u32 decrypt_mode;   // 7C
    u8 key_data0[0x30]; // 80
    int comp_size;      // B0
    int _80;            // B4
    int reserved2[2];   // B8
    u8 key_data1[0x10]; // C0
    u32 tag;            // D0
    u8 scheck[0x58];    // D4
    u32 key_data2;      // 12C
    u32 oe_tag;         // 130
    u8 key_data3[0x1C]; // 134
    u8 main_data;       // 150
} PSP_Header;


typedef struct {
    BootType boot_type;
    BootStorage boot_storage;
    union { // IO operations
        struct {
            int use_fatms371;
            char* tm_path;
            int (*FatMount)();
            int (*FatOpen)(const char*);
            int (*FatRead)(void*, u32);
            int (*FatClose)();
            void (*BtcnfPathHandler)(char* path);
        } psp_io;
        struct {
            int redirect_flash;
            int (*pspemuLfatOpenExtra)(BootFile*);
        } vita_io;
    } extra_io;
    struct { // runtime module, gets injected into boot sequence during reboot
        char *before;
        void *buffer;
        u32 size;
        u32 flags;
    } rtm_mod;
    int (*extraPRXDecrypt)(void *, unsigned int, unsigned int *);
    int (*extraCheckExecFile)(unsigned char *, void *);
    int (*UnpackBootConfig)(char*, int);
} BootLoadExConfig;

#define OE_TAG_PRO 0xC01DB15D
#define OE_TAG_LME 0xC6BA41D3

// fatms371
#define PATH_FATMS_HELPER FLASH0_PATH "kd/_fatmshlp.prx"
#define PATH_FATMS_371 FLASH0_PATH "kd/_fatms371.prx"


extern int psp_model;
extern u32 reboot_end;
extern u32 loadcore_text;
extern BootLoadExConfig* ble_config;
extern BootFileList* boot_files;

// rtm module io flag
extern int rebootmodule_open;

// sceBoot Main Function
extern int (* sceBoot)(int, int, int, int, int, int, int);

// Cache functions
extern void (* sceBootIcacheInvalidateAll)(void);
extern void (* sceBootDacheWritebackInvalidateAll)(void);

// PRX Decrypter Function
extern int (* origPRXDecrypt)(void *, unsigned int, unsigned int *);
extern int (* origCheckExecFile)(unsigned char * addr, void * arg2);
void unPatchLoadCorePRXDecrypt();
void unPatchLoadCoreCheckExec();

// UnpackBootConfig
extern int (* UnpackBootConfig)(char * buffer, int length);
extern u32 UnpackBootConfigCall;
extern u32 UnpackBootConfigArg;

// pspbtcnf functions
int SearchPrx(char *buffer, const char *modname);
int AddPRXNoCopyName(char * buffer, const char * insertbefore, int prxname_offset, u32 flags);
int AddPRX(char * buffer, const char * insertbefore, const char * prxname, u32 flags);
int RemovePrx(char *buffer, const char *prxname, u32 flags);
int MovePrx(char * buffer, const char * insertbefore, const char * prxname, u32 flags);
int ModifyPrxFlag(char *buffer, const char* modname, u32 flags);
int GetPrxFlag(char *buffer, const char* modname, u32 *flags);

// Scanner functions
u32 FindImportRange(char *libname, u32 nid, u32 lower, u32 higher);

// BootLoadEx functions
void configureBoot(BootLoadExConfig*);
void findBootFunctions();
void patchLoadCore(u32 entry);
void patchRebootBuffer();

// PSP IO functions
extern int (* sceBootLfatOpen)(const char * filename);
extern int (* sceBootLfatRead)(char * buffer, int length);
extern int (* sceBootLfatClose)(void);

// PSP specific functions
void patchBootPSP();
int file_exists(const char *path);
int is_fatms371(void);
int patch_bootconf_fatms371(char *buffer, int length);
int patch_bootconf_timemachine(char *buffer, int length);

// Vita specific functions
void patchBootVita();
void relocateFlashFile(BootFile* file);

void flushCache();

#endif
