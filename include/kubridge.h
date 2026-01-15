#ifndef __KULIBRARY__

#define __KULIBRARY__

#ifdef __cplusplus
extern "C"{
#endif

#include <pspsdk.h>
#include <pspkernel.h>
#include <pspsysmem_kernel.h>
#include <pspctrl.h>
#include <psputilsforkernel.h>


// interface for passing arguments to kernel functions
struct KernelCallArg {
    uint32_t arg1;
    uint32_t arg2;
    uint32_t arg3;
    uint32_t arg4;
    uint32_t arg5;
    uint32_t arg6;
    uint32_t arg7;
    uint32_t arg8;
    uint32_t arg9;
    uint32_t arg10;
    uint32_t arg11;
    uint32_t arg12;
    uint32_t ret1;
    uint32_t ret2;
};

/**
 * Functions to let user mode access certain functions only available in
 * kernel mode
*/

/**
  * Load a module using ModuleMgrForKernel.
  * 
  * @param path - The path to the module to load.
  * @param flags - Unused, always 0 .
  * @param option  - Pointer to a mod_param_t structure. Can be NULL.
  *
  * @returns The UID of the loaded module on success, otherwise one of ::PspKernelErrorCodes.
 */
SceUID kuKernelLoadModule(const char *path, int flags, SceKernelLMOption *option);


/**
  * Load a module with a specific apitype
  * 
  * @param apìtype - The apitype
  * @param path - The path to the module to load.
  * @param flags - Unused, always 0 .
  * @param option  - Pointer to a mod_param_t structure. Can be NULL.
  *
  * @returns The UID of the loaded module on success, otherwise one of ::PspKernelErrorCodes.
  */
SceUID kuKernelLoadModuleWithApitype2(int apitype, const char *path, int flags, SceKernelLMOption *option);

/**
 * Gets the api type 
 *
 * @returns the api type in which the system has booted
*/
int kuKernelInitApitype();

/**
 * Gets the filename of the executable to be launched after all modules of the api.
 *
 * @param initfilename - String where copy the initfilename
 * @returns 0 on success
*/
int kuKernelInitFileName(char *initfilename);

/**
 *
 * Gets the device in which the application was launched.
 *
 * @returns the device code, one of PSPBootFrom values.
*/
int kuKernelBootFrom();

/**
 * Get the key configuration in which the system has booted.
 *
 * @returns the key configuration code, one of PSPKeyConfig values 
*/
int kuKernelInitKeyConfig();

/**
 * Get the user level of the current thread
 *
 * @return The user level, < 0 on error
 */
int kuKernelGetUserLevel(void);

/**
 * Set the protection of a block of ddr memory
 *
 * @param addr - Address to set protection on
 * @param size - Size of block
 * @param prot - Protection bitmask
 *
 * @return < 0 on error
 */
int kuKernelSetDdrMemoryProtection(void *addr, int size, int prot);

/**
 * Gets the model of the PSP from user mode.
 * This function is available since 3.60 M33.
 * In previous version, use the kernel function sceKernelGetModel
 *
 * @return one of PspModel values
*/
int kuKernelGetModel(void);

/**
 * Find module by name
 *
 * @param modname - Name of Module
 * @param mod - module structure for output (actually treated as SceModule)
 *
 * @return < 0 on error
 */
int kuKernelFindModuleByName(char *modname, SceModule *mod);

/**
 * Find module by arbitrary memory address
 *
 * @param modname - Memory address somwhere inside the module
 * @param mod - module structure for output (actually treated as SceModule)
 *
 * @return < 0 on error
 */
int kuKernelFindModuleByAddress(void *addr, SceModule *mod);

/**
 * Invalidate the entire instruction cache
 */
void kuKernelIcacheInvalidateAll(void);

/**
 * Read 4 bytes from memory (with kernel memory access)
 *
 * @param addr - Address to read, must have 4 bytes alignment
 */
unsigned int kuKernelPeekw(void *addr);

/**
 * Write 4 bytes to memory (with kernel memory access)
 *
 * @param addr - Address to write, must have 4 bytes alignment
 */
void kuKernelPokew(void *addr, unsigned int value);

/**
 * memcpy (with kernel memory access)
 *
 * @param dest - Destination address
 * @param src - Source address
 * @param num - copy bytes count
 *
 * @return Destination address
 */
void *kuKernelMemcpy(void *dest, const void *src, size_t num);

/**
 * Call a kernel function with kernel privilege
 *
 * @param func_addr - kernel function address
 * @param args - kernel arguments and return values
 *
 * return < 0 on error
 */
int kuKernelCall(void *func_addr, struct KernelCallArg *args);

/**
 * Call a kernel function with kernel privilege and extended stack
 *
 * @param func_addr - kernel function address
 * @param args - kernel arguments and return values
 *
 * return < 0 on error
 */
int kuKernelCallExtendStack(void *func_addr, struct KernelCallArg *args, int stack_size);

void kuKernelGetUmdFile(char *umdfile, int size);

#ifdef __cplusplus
}
#endif

#endif
