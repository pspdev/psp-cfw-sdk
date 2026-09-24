#ifndef __SCTRLLIBRARY_PRO_H__
#define __SCTRLLIBRARY_PRO_H__

/**
 * These functions are only available in SE-C and later, 
 * and they are not in HEN 
*/

enum MsSpeedFlag
{
	MSSPEED_NONE     = 0,
	MSSPEED_POP      = 1,
	MSSPEED_GAME     = 2,
	MSSPEED_VSH      = 3,
	MSSPEED_POP_GAME = 4,
	MSSPEED_GAME_VSH = 5,
	MSSPEED_VSH_POP  = 6,
	MSSPEED_ALWAYS   = 7,
};

enum BootLoadFlags
{
	BOOTLOAD_VSH = 1,
	BOOTLOAD_GAME = 2,
	BOOTLOAD_UPDATER = 4,
	BOOTLOAD_POPS = 8,
	BOOTLOAD_UMDEMU = 64, /* for original NP9660 */
};

enum CachePolicy
{
	CACHE_POLICY_LRU = 0,
	CACHE_POLICY_RR = 1,
};

#endif
