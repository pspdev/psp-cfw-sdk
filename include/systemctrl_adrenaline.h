#ifndef _SYSTEMCTRL_EPI_H_
#define _SYSTEMCTRL_EPI_H_

#include <psploadcore.h>

enum InfernoCacheConf {
	CACHE_CONFIG_LRU,
    CACHE_CONFIG_RR,
	CACHE_CONFIG_OFF,
};

enum IsoCacheNumberConf {
	ISO_CACHE_NUM_AUTO,
	ISO_CACHE_NUM_001,
	ISO_CACHE_NUM_002,
	ISO_CACHE_NUM_004,
	ISO_CACHE_NUM_008,
	ISO_CACHE_NUM_016,
	ISO_CACHE_NUM_032,
	ISO_CACHE_NUM_064,
	ISO_CACHE_NUM_128,
};

enum IsoCacheSizeConf {
	ISO_CACHE_SIZE_AUTO,
	ISO_CACHE_SIZE_01KB,
	ISO_CACHE_SIZE_02KB,
	ISO_CACHE_SIZE_04KB,
	ISO_CACHE_SIZE_08KB,
	ISO_CACHE_SIZE_16KB,
	ISO_CACHE_SIZE_32KB,
	ISO_CACHE_SIZE_64KB,
};

enum ForceHighMemory {
	HIGHMEM_OPT_OFF,
	HIGHMEM_OPT_STABLE,
	HIGHMEM_OPT_MAX,
};

enum RecoveryColor {
	RECOVERY_COLOR_BLUE,
	RECOVERY_COLOR_GREEN,
	RECOVERY_COLOR_RED,
	RECOVERY_COLOR_GRAY,
	RECOVERY_COLOR_PINK,
	RECOVERY_COLOR_PURPLE,
	RECOVERY_COLOR_CYAN,
	RECOVERY_COLOR_ORANGE,
	RECOVERY_COLOR_YELLOW,
	RECOVERY_COLOR_B_WHITE,
	RECOVERY_COLOR_B_RED,
	RECOVERY_COLOR_B_GREEN,
	RECOVERY_COLOR_B_BLUE,
};

enum ExtendedColors {
	EXTENDED_COLOR_DISABLED,
	/** PSP 2000 Extended Color */
	EXTENDED_COLOR_02G,
	/** PSP 3000 Extended Color */
	EXTENDED_COLOR_03G,
};

enum HidePicsOpt {
	PICS_OPT_DISABLED,
	PICS_OPT_BOTH,
	PICS_OPT_PIC0_ONLY,
	PICS_OPT_PIC1_ONLY,
};

enum IsoUmdMode {
	ISO_MODE_INFERNO,
	ISO_MODE_MARCH33,
	ISO_MODE_NP9660,
};

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int sctrlGetUsbState();
int sctrlStartUsb();
int sctrlStopUsb();
int sctrlRebootDevice();

/**
 *  Find a import library stub table.
 *
 * @param mod The module where to search the function.
 * @param library The library name.
 *
 * @return The reference to the stub table ot NULL if not found.
 */
SceLibraryStubTable* sctrlHENFindImportLib(SceModule* mod, const char* library);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SYSTEMCTRL_EPI_H_ */