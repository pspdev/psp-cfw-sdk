#ifndef __VSHCTRL_H__
#define __VSHCTRL_H__

#include <stddef.h>
#include <pspsdk.h>
#include <pspctrl.h>

#include <systemctrl_se.h>

#define SENSE_KEY (PSP_CTRL_CIRCLE|PSP_CTRL_TRIANGLE|PSP_CTRL_CROSS|PSP_CTRL_SQUARE|PSP_CTRL_START|PSP_CTRL_SELECT)

#define ALL_ALLOW    (PSP_CTRL_UP|PSP_CTRL_RIGHT|PSP_CTRL_DOWN|PSP_CTRL_LEFT)
#define ALL_BUTTON   (PSP_CTRL_TRIANGLE|PSP_CTRL_CIRCLE|PSP_CTRL_CROSS|PSP_CTRL_SQUARE)
#define ALL_TRIGGER  (PSP_CTRL_LTRIGGER|PSP_CTRL_RTRIGGER)
#define ALL_FUNCTION (PSP_CTRL_SELECT|PSP_CTRL_START|PSP_CTRL_HOME|PSP_CTRL_HOLD|PSP_CTRL_NOTE)
#define ALL_CTRL     (ALL_ALLOW|ALL_BUTTON|ALL_TRIGGER|ALL_FUNCTION)
#define FORCE_LOAD   (PSP_CTRL_SELECT|ALL_TRIGGER)


/**
 * This API is for VSH menu, XMB control or any other VSH/XMB plugin.
 *
 * Note: when referring to CSO, other compressed formats (ZSO, JSO, DAX) also apply.
*/

/**
 * The control handler for the VSH menu.
 */
typedef int (*VSHMENU_CTRL_HANDLER)(SceCtrlData *ctrl_data, int count);

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Helper function to allocate memory on P2 (user memory).
 *
 * @param size The amount of bytes to allocate.
 *
 * @return A pointer to allocated buffer, or `NULL` on error.
 *
 * @attention Requires linking to `pspsysc_user` stub to be available.
 *
 * @note Available on ARK and Epinephrine (>= v8.0.0).
 */
void* user_malloc(size_t size);

/**
 * Helper function to allocate aligned memory on P2 (user memory).
 *
 * @param align The alignment.
 * @param size The amount of bytes to allocate.
 *
 * @return A pointer to allocated buffer, or `NULL` on error.
 *
 * @attention Requires linking to `pspsysc_user` stub to be available.
 *
 * @note Available on ARK and Epinephrine (>= v8.0.0).
 */
void* user_memalign(unsigned int align, unsigned int size);

/**
 * Deallocate memory allocated by user_malloc.
 *
 * @param ptr A pointer to the allocated memory.
 *
 * @attention Requires linking to `pspsysc_user` stub to be available.
 *
 * @note Available on ARK and Epinephrine (>= v8.0.0).
 */
void user_free(void* ptr);

/**
 * Registers the vsh menu.
 * When HOME is pressed, vshctrl will load the satelite module.
 * In module_start, call this function to register the vsh menu.
 *
 * @param[in] ctrl The function that will be executed each time
 * the system calls `ReadBufferPositive`. Despite `satelite.prx` being
 * an user module, this function will be executed in kernel mode.
 *
 * @returns `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspvshctrl` stub to be available.
 *
 * @note Available on M33, LME, PRO, ARK and Epinephrine.
 */
int vctrlVSHRegisterVshMenu(VSHMENU_CTRL_HANDLER ctrl);


/**
 * Register VSH Menu drawing function.
 *
 * @param[in] vshmenu_draw the function that will draw the vshmenu onto screen
 *
 * @returns `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspvshctrl` stub to be available.
 *
 * @note Available on ARK (>= v5.0.0) and Epinephrine (>= v8.0.0).
 */
int vctrlVSHRegisterVshGuMenu(void (*vshmenu_draw)(void* frame));

/**
 * Exits the vsh menu.
 *
 * vshmenu module must call this module after destroying vsh menu display and
 * freeing resources.
 *
 * vshmenu module doesn't need to stop-unload itself, as that is vshctrl job.
 *
 * @param[in] conf Indicates the new config. VshCtrl will update the internal
 * vshctrl and systemctrl variables with the new configuration given by this
 * param. However is job of `satelite.prx` to save those settings to the
 * configuration file, using `sctrlSESetConfig()`.
 *
 * @returns `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspvshctrl` stub to be available.
 *
 * @note Available on M33, LME, PRO, ARK and Epinephrine.
 */
int vctrlVSHExitVSHMenu(SEConfig *conf, char *videoiso, int disctype);

int vctrlVSHExitVSHMenuEx(SEConfig *g_conf, int g_size, char *videoiso, int disctype);

/**
 * Sets SE configuration.
 *
 * @param[in] conf Indicates the new config. Vshctrl will update the internal
 * vshctrl and systemctrl variables with the new configuration given by this param.
 * However is job of `satelite.prx` to save those settings to the configuration file.
 * using `sctrlSESetConfig`.
 *
 * @returns `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspvshctrl` stub to be available.
 *
 * @note Available on PRO, ARK and Epinephrine (>= v8.0.0).
 */
int vctrlVSHUpdateConfig(SEConfig *config);


/**
 * Detect the UMD type of an ISO.
 *
 * @param[in] path The full path to the ISO or Compressed ISO file.
 *
 * @returns The disc type on success, `< 0` on error.
 *
 * @attention Requires linking to `pspvshctrl` stub to be available.
 *
 * @note Available on PRO, ARK and Epinephrine (>= v8.0.0).
 */
int vshDetectDiscType(const char *path);


/**
 * Check if PSP Go has a hibernation (paused game).
 *
 * @returns boolean.
 *
 * @attention Requires linking to `pspvshctrl` stub to be available.
 *
 * @note Available on ARK (>= v5.0.0).
 */
int vshCtrlHibernationExists();

/**
 * Delete PSP Go hibernation (paused game).
 *
 * @returns `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspvshctrl` stub to be available.
 *
 * @note Available on PRO and ARK.
 */
int vshCtrlDeleteHibernation();


/**
 * Open an ISO (or CSO) for reading.
 *
 * @param[in] path The full path to the ISO (or CSO) file.
 *
 * @returns `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspvshctrl` stub to be available.
 *
 * @note Available on ARK.
 */
int isoOpen(const char *path);


/**
 * Raw sector read of currently opened ISO.
 *
 * @param buffer - pointer to where data will be stored.
 * @param lba - Logical Block Address of the ISO. Each ISO block is 2048 bytes in size.
 * @param offset - offset within the LBA to start reading data from.
 * @param size - amount of bytes to read into provided buffer.
 *
 * @returns amount of actual bytes read into buffer, < 0 on error.
 *
 * @attention Requires linking to `pspvshctrl` stub to be available.
 *
 *  @note Available on ARK.
 */
int isoRead(void *buffer, u32 lba, int offset, u32 size);


/**
 * Closes the currently opened ISO, if there was one.
 *
 * @attention Requires linking to `pspvshctrl` stub to be available.
 *
 *  @note Available on ARK.
 */
void isoClose();


/**
 * Get information about a file inside the currently opened ISO.
 * Information retrieved is the file size and LBA where the file starts
 *  (all files in an ISO are aligned by ISO block size - a file does not start in the middle of a block).
 *
 * @param path - path of the file inside the ISO that you want to scan.
 * @param filesize - pointer to an unsigned 32 bit integer where the size of the file will be stored.
 * @param lba - pointer to an unsigned 32 bit integer where the starting LBA of the file will be stored.
 *
 * @returns 0 on success, < 0 on error.
 *
 * @attention Requires linking to `pspvshctrl` stub to be available.
 *
 *  @note Available on ARK.
 */
int isoGetFileInfo(const char * path, u32 *filesize, u32 *lba);


/**
 * Get total amount of sectors/blocks in the currently opened ISO.
 * Each standard ISO sector/block is 2048 bytes in size.
 * Not to be confused with CSO sectors/blocks, which can be of any arbitrary size.
 *
 * @returns total number of sectors in the currently opened ISO file.
 *
 * @attention Requires linking to `pspvshctrl` stub to be available.
 *
 * @note Available on ARK.
 */
int isoGetTotalSectorSize();


/**
 * Helper function to detect if an ISO (or CSO) has been patched with Prometheus Patches.
 *
 * @param isopath - full path of the ISO (or CSO) file.
 *
 * @returns boolean - 1 if patched, 0 if unpatched.
 *
 * @attention Requires linking to `pspvshctrl` stub to be available.
 *
 * @note Available on ARK.
 */
int has_prometheus_module(const char *isopath);


/**
 * Helper function to detect if an ISO (or CSO) has an update (PBOOT.PBP) available to use.
 *
 * @param isopath - full path of the ISO (or CSO) file.
 *
 * @returns boolean - 1 if update available, 0 if unavailable.
 *
 * @attention Requires linking to `pspvshctrl` stub to be available.
 *
 * @note Available on ARK.
 */
int has_update_file(const char *isopath, char* update_file);


/**
 * Obtain the value of a registry variable.
 *
 * @param[in] dir The registry directory.
 * @param[in] name The variable name.
 * @param[out] val A pointer to an unsigned 32 bit integer where the value will be
 * stored.
 *
 * @return `0` if registry not found, `1` otherwise.
 *
 * @attention Requires linking to `pspvshctrl` stub to be available.
 *
 * @note Available on ARK and Epinephrine (>= v8.0.0).
 */
int vctrlGetRegistryValue(const char *dir, const char *name, u32 *val);


/**
 * Set the value of a registry variable.
 *
 * @param[in] dir The registry directory.
 * @param[in] name The variable name.
 * @param val The new value of the variable.
 *
 * @return `0` if registry not found, `1` value was set.
 *
 * @attention Requires linking to `pspvshctrl` stub to be available.
 *
 * @note Available on ARK and Epinephrine (>= v8.0.0).
 */
int vctrlSetRegistryValue(const char *dir, const char *name, u32 val);

/**
 * Set recovery flag for next reboot.
 *
 * @attention Requires linking to `pspvshctrl` stub to be available.
 *
 * @note Available on LME, ARK (>= 5.3.0) and Epinephrine (>= 8.1.0).
 */
void vctrlVSHSetRecovery(void);

/**
 * Set VSH CPU/BUS speed.
 *
 * @attention Requires linking to `pspvshctrl` stub to be available.
 *
 * @note Available on LME, ARK (>= 5.3.0) and Epinephrine (>= 8.1.0).
 */
void vctrlVSHSetSpeed(int cpu, int bus );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __VSHCTRL_H__ */

