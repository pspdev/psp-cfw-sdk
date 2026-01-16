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

#ifndef _SYSTEMCTRL_H_
#define _SYSTEMCTRL_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <pspsdk.h>
#include <psploadexec_kernel.h>
#include <pspiofilemgr_kernel.h>
#include <pspthreadman_kernel.h>
#include <psploadcore.h>
#include <pspkernel.h>
#include <pspinit.h>

#include <rebootexconfig.h>

#define GAME_ID_MINIMUM_BUFFER_SIZE 10

// Different PSP models
enum {
    PSP_1000 = 0,   // 01g
    PSP_2000 = 1,   // 02g
    PSP_3000 = 2,   // 03g
    PSP_4000 = 3,   // 04g
    PSP_GO   = 4,   // 05g
    PSP_7000 = 6,   // 07g
    PSP_9000 = 8,   // 09g
    PSP_11000 = 10, // 11g
};

enum BootLoadFlags
{
    BOOTLOAD_VSH = 1,
    BOOTLOAD_GAME = 2,
    BOOTLOAD_UPDATER = 4,
    BOOTLOAD_POPS = 8,
    BOOTLOAD_UMDEMU = 64, /* for original NP9660 */
};

// Console type (value returned by sctrlHENIsToolKit)
enum ToolkitType
{
    PSP_TOOLKIT_TYPE_RETAIL = 0, // retail unit (not a toolkit)
    PSP_TOOLKIT_TYPE_TEST = 1, // testing tool kit
    PSP_TOOLKIT_TYPE_DEV = 2, // development tool kit
};

// Custom Utility Modules
#define PSP_MODULE_NET_FTP             0x0180
#define PSP_MODULE_AV_PNG              0x0380
#define PSP_MODULE_AV_HELPER           0x0390
#define PSP_MODULE_VLF                 0x0700
#define PSP_MODULE_INTRAFONT_VLF       0x0701
#define PSP_MODULE_INTRAFONT_GU        0x0702
#define PSP_MODULE_UNARCHIVER          0x0710
#define PSP_MODULE_USB_DEV_DRV         0x0800
#define PSP_MODULE_IDS_REGEN           0x0801
#define PSP_MODULE_IO_PRIVILEGED       0x0802
#define PSP_MODULE_PSAR_DUMPER         0x0803
#define PSP_MODULE_PSPDECRYPT          0x0804
#define PSP_MODULE_KPSPIDENT           0x0805
#define PSP_MODULE_IPL_UPDATER         0x0806
#define PSP_MODULE_KBOOTI_UPDATER      0x0807


// Function Name Clones (of old but gold times)
//#define sctrlKernelQuerySystemCall sceKernelQuerySystemCall

// Prologue Module Start Handler
typedef int (* STMOD_HANDLER)(SceModule *);

// data for HijackFunction
typedef struct FunctionPatchData{
    unsigned int __instr__[5];
    unsigned int __extra_[3];
} FunctionPatchData;

// Decrypt extension functions
typedef int (* KDEC_HANDLER)(u32 *buf, int size, int *retSize, int m);
typedef int (* MDEC_HANDLER)(u32 *tag, u8 *keys, u32 code, u32 *buf, int size, int *retSize, int m, void *unk0, int unk1, int unk2, int unk3, int unk4);

// patch helper functions
u32 sctrlHENFindJALGeneric(u32 addr, int reversed, int skip);
#define sctrlHENFindFirstJAL(addr) sctrlHENFindJALGeneric(addr, 0, 0)
#define sctrlHENFindFirstJALReverse(addr) sctrlHENFindJALGeneric(addr, 1, 0)
#define sctrlHENFindJAL(addr, pos) sctrlHENFindJALGeneric(addr, 0, pos)
#define sctrlHENFindJALReverse(addr, pos) sctrlHENFindJALGeneric(addr, 1, pos)
#define sctrlHENFindFirstJALForFunction(modname, libname, uid) sctrlHENFindFirstJAL(sctrlHENFindFunction(modname, libname, uid))
#define sctrlHENFindJALForFunction(modname, libname, uid, pos) sctrlHENFindJAL(sctrlHENFindFunction(modname, libname, uid), pos)
#define sctrlHENFindFirstJALReverseForFunction(modname, libname, uid) sctrlHENFindFirstJALReverse(sctrlHENFindFunction(modname, libname, uid))
#define sctrlHENFindJALReverseForFunction(modname, libname, uid, pos) sctrlHENFindJALReverse(sctrlHENFindFunction(modname, libname, uid), pos)

u32 sctrlHENFindFirstBEQ(u32 addr);
u32 sctrlHENFindRefInGlobals(char* libname, u32 addr, u32 ptr);

int sctrlHENIsSystemBooted();

/**
 *  Find Import Library Stub Table
 */
SceLibraryStubTable * sctrlFindImportLib(SceModule * pMod, char * library);

/**
 *  Find Import Function Stub Address
 */
unsigned int sctrlFindImportByNID(SceModule * pMod, const char * library, unsigned int nid);

/**
 *  Replace Import Function Stub
 */
int sctrlHookImportByNID(SceModule * pMod, const char * library, unsigned int nid, void * func);

/**
 * Restart the vsh.
 *
 * @param param - Pointer to a ::SceKernelLoadExecVSHParam structure, or NULL
 *
 * @returns < 0 on some errors.
 *
 */
int sctrlKernelExitVSH(struct SceKernelLoadExecVSHParam *param);

/**
 *  Calculate Random Number via KIRK
 */
unsigned int sctrlKernelRand(void);

/**
 * Register Custom init.prx sceKernelStartModule Handler, returns previous handler (if any)
 */
void* sctrlSetStartModuleExtra(int (* func)(int modid, SceSize argsize, void * argp, int * modstatus, SceKernelSMOption * opt));

/**
 * Read parameter from an SFO file or an EBOOT.PBP file
 */
int sctrlGetSfoPARAM(const char* sfo_path, const char * paramName, u16 * paramType, u32 * paramLength, void * paramBuffer);

/**
 * Get SFO param from currently running game/app
 */
int sctrlGetInitPARAM(const char * paramName, u16 * paramType, u32 * paramLength, void * paramBuffer);

/**
 * Find UID of the specified Thread
 */
int sctrlGetThreadUIDByName(const char * name);

/**
 * Return Thread Context of specified Thread (Search by UID)
 */
int sctrlGetThreadContextByUID(int uid, SceKernelThreadKInfo * ctx);

/**
 * Return Thread Context of specified Thread (Search by Name)
 */
int sctrlGetThreadContextByName(const char * name, SceKernelThreadKInfo * ctx);

/**
 * Flush Instruction and Data Cache
 */
void sctrlFlushCache(void);

/**
 * Missing PSPSDK Functions
 */
u32 sceKernelQuerySystemCall(void * function);

/**
 * Register the default VRAM handler for PSX exploit, returns the previous handler
 */
void* sctrlHENSetPSXVramHandler(void (*handler)(u32* psp_vram, u16* ps1_vram));

/**
 * DEFLATE decompress
 */
int sctrlDeflateDecompress(void* dest, void* src, int size);

/**
 * GZIP decompress
 */
int sctrlGzipDecompress(void* dest, void* src, int size);

/**
 * LZ4 decompress
 */
int LZ4_decompress_fast(const char* source, char* dest, int outputSize);
#define sctrlLz4Decompress(dest, src, size) LZ4_decompress_fast(src, dest, size)

/**
 * LZO decompress
 */
int lzo1x_decompress(void* source, unsigned src_len, void* dest, unsigned* dst_len, void*);
#define sctrlLzoDecompress(dest, dst_size, src, src_size) lzo1x_decompress(src, src_size, dest, dst_size, NULL)

/**
 * Check if currently running with ms0 being redirected to ef0.
 */
int sctrlKernelMsIsEf();

/**
 * LoadExec for physical UMD game.
 *
 * @param file - The file to execute, usually EBOOT.BIN inside disc0.
 * @param param - Pointer to a ::SceKernelLoadExecVSHParam structure, or NULL.
 *
 * @returns < 0 on some errors. 
 */
int sctrlKernelLoadExecVSHDisc(const char *file, struct SceKernelLoadExecVSHParam *param);

/**
 * Restart the vsh.
 *
 * @param param - Pointer to a ::SceKernelLoadExecVSHParam structure, or NULL
 *
 * @returns < 0 on some errors.
 *
 */
int sctrlKernelExitVSH(struct SceKernelLoadExecVSHParam *param);

/**
 * Executes a new executable from a disc.
 * It is the function used by the firmware to execute the EBOOT.BIN from a disc.
 *
 * @param file - The file to execute.
 * @param param - Pointer to a ::SceKernelLoadExecVSHParam structure, or NULL.
 *
 * @returns < 0 on some errors. 
 */
int sctrlKernelLoadExecVSHDisc(const char *file, struct SceKernelLoadExecVSHParam *param);

/**
 * Executes a new executable from a disc.
 * It is the function used by the firmware to execute an updater from a disc.
 *
 * @param file - The file to execute.
 * @param param - Pointer to a ::SceKernelLoadExecVSHParam structure, or NULL.
 *
 * @returns < 0 on some errors. 
 */
int sctrlKernelLoadExecVSHDiscUpdater(const char *file, struct SceKernelLoadExecVSHParam *param);

/**
 * Executes a new executable from a memory stick.
 * It is the function used by the firmware to execute an updater from a memory stick.
 *
 * @param file - The file to execute.
 * @param param - Pointer to a ::SceKernelLoadExecVSHParam structure, or NULL.
 *
 * @returns < 0 on some errors. 
 */
int sctrlKernelLoadExecVSHMs1(const char *file, struct SceKernelLoadExecVSHParam *param);

/**
 * Executes a new executable from a memory stick.
 * It is the function used by the firmware to execute games (and homebrew :P) from a memory stick.
 *
 * @param file - The file to execute.
 * @param param - Pointer to a ::SceKernelLoadExecVSHParam structure, or NULL.
 *
 * @returns < 0 on some errors. 
 */
int sctrlKernelLoadExecVSHMs2(const char *file, struct SceKernelLoadExecVSHParam *param);

/**
 * Executes a new executable from PSP Go's Internal Memory.
 * It is the function used by the firmware to execute games (and homebrew :P) from internal memory.
 *
 * @param file - The file to execute.
 * @param param - Pointer to a ::SceKernelLoadExecVSHParam structure, or NULL.
 *
 * @returns < 0 on some errors. 
 */
int sctrlKernelLoadExecVSHEf2(const char *file, struct SceKernelLoadExecVSHParam *param);

/**
 * Executes a new executable from a memory stick.
 * It is the function used by the firmware to execute ... ?
 *
 * @param file - The file to execute.
 * @param param - Pointer to a ::SceKernelLoadExecVSHParam structure, or NULL.
 *
 * @returns < 0 on some errors. 
 */
int sctrlKernelLoadExecVSHMs3(const char *file, struct SceKernelLoadExecVSHParam *param);

/**
 * Executes a new executable from a memory stick.
 * It is the function used by the firmware to execute psx games
 *
 * @param file - The file to execute.
 * @param param - Pointer to a ::SceKernelLoadExecVSHParam structure, or NULL.
 *
 * @returns < 0 on some errors. 
 */
int sctrlKernelLoadExecVSHMs4(const char *file, struct SceKernelLoadExecVSHParam *param);


/**
 * Executes a new executable with the specified apitype
 *
 * @param apitype - The apitype
 * @param file - The file to execute.
 * @param param - Pointer to a ::SceKernelLoadExecVSHParam structure, or NULL.
 *
 * @returns < 0 on some errors. 
 */
int sctrlKernelLoadExecVSHWithApitype(int apitype, const char *file, struct SceKernelLoadExecVSHParam *param);

/**
 * Sets the api type 
 *
 * @param apitype - The apitype to set
 * @returns the previous apitype
 *
 * @Note - this will modify also the value of sceKernelBootFrom, since the value of
 * bootfrom is calculated from the apitype
 */
int sctrlKernelSetInitApitype(int apitype);

/**
 * Sets the filename of the launched executable.
 *
 * @param filename - The filename to set
 * @returns 0 on success
 */
int sctrlKernelSetInitFileName(char * filename);

/**
 * Sets the init key config
 *
 * @param key - The key code
 * @returns the previous key config
 */
int sctrlKernelSetInitKeyConfig(int key);

/**
 * Sets the user level of the current thread
 *
 * @param level - The user level
 * @return the previous user level on success
 */
int sctrlKernelSetUserLevel(int level);

/**
 * Sets the devkit version
 * 
 * @param version - The devkit version to set
 * @return the previous devkit version
 * 
 */
int sctrlKernelSetDevkitVersion(int version);

/**
 * Checks if we are in SE.
 *
 * @returns 1 if we are in SE-C or later, 0 if we are in HEN-D or later,
 * and < 0 (a kernel error code) in any other case
 */
int sctrlHENIsSE();

/**
 * Checks if we are in Devhook.
 *
 * @returns 1 if we are in SE-C/HEN-D for devhook  or later, 0 if we are in normal SE-C/HEN-D or later,
 * and < 0 (a kernel error code) in any other case
 */
int sctrlHENIsDevhook();

/**
 * Gets the HEN version
 *
 * @returns - The HEN version
 *
 * HEN D / SE-C :  0x00000400
 */
int sctrlHENGetVersion();

/**
 * Gets the HEN minor version
 *
 * @returns - The HEN minor version
 */
int sctrlHENGetMinorVersion();

/**
 * Check if currently running on a toolkit.
 *
 * @return 0 if retail, 1 if TestingTool, 2 if DevelopmentTool
 */
int sctrlHENIsToolKit();

/**
 * Finds a driver
 *
 * @param drvname - The name of the driver (without ":" or numbers)
 *
 * @returns the driver if found, NULL otherwise
 *
 */
PspIoDrv *sctrlHENFindDriver(const char *drvname);

/** 
 * Finds a function.
 *
 * @param modname - The module where to search the function
 * @param libname - The library name
 * @nid - The nid of the function
 *
 * @returns - The function address or 0 if not found
 *
 */
unsigned int sctrlHENFindFunction(const char *modname, const char *libname, unsigned int nid);

/**
 * Finds an exported function in a ::SceModule.
 *
 * Good to optimize when you already have a ::SceModule module and wants to
 * find a function in that module.
 *
 * @param mod - The module where to search the function
 * @param library - The library name
 * @param nid - The nid of the function
 *
 * @returns - The function address or 0 if not found
 *
*/
unsigned int sctrlHENFindFunctionInMod(SceModule * mod, const char *library, unsigned int nid);

/** 
 * Finds an import.
 *
 * @param modname - The module where to search the function
 * @param libname - The library name
 * @nid - The nid of the function
 *
 * @returns - The function address or 0 if not found
 *
 */
unsigned int sctrlHENFindImport(const char *modname, const char *libname, unsigned int nid);

/** 
 * Finds an import.
 *
 * @param mod - The module where to search the function
 * @param libname - The library name
 * @nid - The nid of the function
 *
 * @returns - The function address or 0 if not found
 *
 */
unsigned int sctrlHENFindImportInMod(SceModule *mod, const char *libname, unsigned int nid);

/**
 * Hijack a function.
 * Stackable function hijacking.
 * 
 * @param patch_data buffer to store data for the patch.
 * @param func_addr address of function to be hijacked
 * @param patch_func function that will take over
 * @param orig_func pointer to a pointer, will store pointer to call original (or next) function.
 * 
 */
void sctrlHENHijackFunction(FunctionPatchData* patch_data, void* func_addr, void* patch_func, void** orig_func);

/**
 * Sets a function to be called just before module_start of a module is gonna be called (useful for patching purposes)
 *
 * @param handler - The function, that will receive the module structure before the module is started.
 *
 * @returns - The previous set function (NULL if none);
 * @Note: because only one handler function is handled by HEN, you should
 * call the previous function in your code.
 *
 * @Example: 
 *
 * STMOD_HANDLER previous = NULL;
 *
 * int OnModuleStart(SceModule *mod);
 *
 * void somepointofmycode()
 * {
 *        previous = sctrlHENSetStartModuleHandler(OnModuleStart);
 * }
 *
 * void OnModuleStart(SceModule *mod)
 * {
 *        if (strcmp(mod->modname, "vsh_module") == 0)
 *        {
 *            // Do something with vsh module here
 *        }
 *
 *        // Call previous handler
 *        if (previous) previous(mod);
 * }
 *
 * @Note2: The above example should be compiled with the flag -fno-pic
 *            in order to avoid problems with gp register that may lead to a crash.
 *
 */
STMOD_HANDLER sctrlHENSetStartModuleHandler(STMOD_HANDLER new_handler);

/**
 * Creates a syscall stub for the given `function` in user-memory.
 *
 * Creating a syscall stub this way allows a kernel program to inject syscall
 * calls in a user module without overwriting a existing syscall stub in the
 * module being modified.
 *
 * @note The given `function` must be exported as syscall for it to work.
 *
 * @param function The function pointer to the function to create the syscall stub
 *
 * @return The syscall stub of the given function (> 0). Or zero if the function fails to create the stub.
 *
 * @attention Every call to this function allocates 8 bytes of memory in the
 * user RAM, which is also the available memory for the running application. So,
 * avoid excessive use of this function.
 */
unsigned int sctrlHENMakeSyscallStub(void *function);

/**
 * Sets the speed (only for kernel usage)
 *
 * @param cpu - The cpu speed
 * @param bus - The bus speed
 */
void sctrlHENSetSpeed(int cpu, int bus);

/**
 * Unlocks extra memory on partition 2 on next reboot. This feature is only available in PSP 2g+ and PS Vita.
 * This function has been deprecated in ARK and has no effect. Use sctrlHENApplyMemory instead.
 *
 * @param p2 - Size of user partition.
 * @param p8 - Size of extra ram partion.
 *
 * @returns 0
 */
int sctrlHENSetMemory(u32 p2, u32 p8);

/**
 * Unlocks extra memory on partition 2. This feature is only available in PSP 2g+ and PS Vita.
 *
 * @param p2 - The size in MB for the user partition. The actual value is ignored but must be > 24.
 *
 * @returns 0 on success, -1 if can't unlock (i.e. pops, vsh, 1k), -2 if already unlocked, -3 if too late to unlock.
 */
int sctrlHENApplyMemory(u32 p2);

/**
 * Obtain the syscall number of a given user-exported kernel function.
 * 
 * @param func_addr: absolute address of kernel function.
 * 
 * @returns syscall number on success, <0 on error.
 */
int sctrlKernelQuerySystemCall(void *func_addr);

/**
 * Obtain boot device
 * 
 * @returns boot device.
 */
int sctrlKernelBootFrom(void);

/**
 * Sets the partition 2 and 8  memory for next loadexec.
 *
 * @param p2 - The size in MB for the user partition. Must be > 0
 * @param p8 - The size in MB for partition 8. Can be 0.
 *
 * @returns 0 on success, < 0 on error.
 * This function is only available in the slim. The function will fail
 * if p2+p8 > 52 or p2 == 0
 */

void sctrlHENPatchSyscall(void *addr, void *newaddr);

/**
 * Patch module by offset
 *
 * @param modname - module name
 * @param inst  - instruction
 * @param offset - module patch offset
 *
 * @return < 0 on error
 */
int sctrlPatchModule(char *modname, u32 inst, u32 offset);

/**
 * Get module text address
 *
 * @param modname - module name
 * 
 * @return text address, or 0 if not found
 */
u32 sctrlModuleTextAddr(char *modname);

/**
 * Get sceInit module text address
 *
 * @note Only useful before sceInit exits
 *
 * @return text address, or 0 if not found
 */
u32 sctrlGetInitTextAddr(void);

/**
 * Set custom start module handler
 * It can be used to replace a system module
 *
 * @note: func returns -1 to ignore the module and load the original module. Or new modid if replace is done.
 */
void sctrlSetCustomStartModule(int (*func)(int modid, SceSize argsize, void *argp, int *modstatus, SceKernelSMOption *opt));

/**
 * Loads a module on next reboot. Only kernel mode.
 *
 * @param module_after - The path of the module which is loaded after the module to be loaded.
   The module passed to this function will be loaded just before that module.
 * @param buf - The buffer containing the module - Don't deallocate this one. It has to reside in kernel memory.
 * @param size - The size of the module
 * @param flags - The modes in which the module should be loaded, one of BootLoadFlags
 *
 * @Example:
 * sctrlHENLoadModuleOnReboot("/kd/usersystemlib.prx", module_buffer, module_size, BOOTLOAD_GAME | BOOTLOAD_POPS | BOOTLOAD_UMDEMU); 
 *
 * This will load the module contained in module_buffer just before /kd/usersystemlib.prx in the next reboot, if the mode of next reboot is game, pops or umdemu
 *
 * @Remarks: Don't use too early modules in first param like "/kd/init.prx" or "/kd/systemctrl.prx", or your module may not load properly
 * Only one module will be loaded on reboot with this function. 
 * If this function is called many times, only the last one will be considered.
 * By making a module to load itself using this function, and calling 
 * sctrlHENLoadModuleOnReboot on module_start, a prx can cause itself to be resident in the modes choosen by flags.
 * If all flags are selected, the module will stay resident until a psp shutdown, or until sctrlHENLoadModuleOnReboot is not called.
 */
void sctrlHENLoadModuleOnReboot(char *module_after, void *buf, int size, int flags);

/**
 * Override rebootex.
 */
void sctrlHENSetRebootexOverride(const u8 *rebootex);

/**
 * Enable/disable NID Resolver on particular library
 *
 * @param libname the name of the library to be enabled/disabled
 * @param enabled 0 - disabled, != 0 - enabled
 *
 * @Example:
 * sctrlKernelSetNidResolver("sceImpose_driver", 0); // disable sceImpose_driver resolving
 *
 * @return previous value if set, < 0 on error
 */
int sctrlKernelSetNidResolver(char *libname, u32 enabled);

/**
 * Get the real unspoofed Ethernet (MAC) Address of the systems WLAN chip
 *
 * @param mac Out-Buffer (6B) for real MAC Address
 *
 * @return 0 on success, < 0 on error
 */
int sctrlGetRealEthernetAddress(uint8_t * mac);

/**
 * Wrapper for sceKernelDeflateDecompress
 *
 * @param dest out buffer where the decompressed data will be
 * @param src source buffer with the compressed data
 * @param size size of the decompressed data
 *
 */
int sctrlDeflateDecompress(void* dest, void* src, int size);

/**
 * Obtain RebootexConfig structure. Needs to be casted correctly based on running CFW.
 */
RebootexConfig* sctrlHENGetRebootexConfig(RebootexConfig*);


/**
 * Resolve a NID.
 * Obtains the new version of a NID given the older version.
 * 
 * @param libName library name
 * @param nid old NID
 * 
 * @return new NID
 * 
 */
unsigned int sctrlKernelResolveNid(const char * libName, unsigned int nid);


#ifdef __cplusplus
}
#endif

#endif
