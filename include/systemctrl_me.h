#ifndef __SYSTEMCTRL_ME_H__
#define __SYSTEMCTRL_ME_H__


#include <pspsdk.h>
#include <pspkernel.h>
#include <psploadexec_kernel.h>
#include <pspinit.h>
#include <psploadcore.h>

enum BootLoadFlags
{
	BOOTLOAD_VSH = 1,
	BOOTLOAD_GAME = 2,
	BOOTLOAD_UPDATER = 4,
	BOOTLOAD_POPS = 8,
	BOOTLOAD_UMDEMU = 64, /* for original NP9660 */
};

enum MEUmdModes
{
	ME_MODE_UMD = 0,
	ME_MODE_OE_LEGACY = 1,
	ME_MODE_MARCH33 = 2,
	ME_MODE_NP9660 = 3,
	ME_MODE_ME = 4,
	ME_MODE_INFERNO = 5,
};

enum InfernoCachePolicy
{
	CACHE_POLICY_LRU = 0,
	CACHE_POLICY_RR  = 1,
};

#define MINI_MAGIC			0x3031454D
#define TMENU_MAX			16
#define MAX_HIGH_MEMSIZE	55

typedef struct{
	u32 magic;
	int vsh_color;
	int recovery_color;
	int menu_switch[TMENU_MAX];
}VshConfig;

void* sctrlKernelGetPartition(int pid);

#define FindProc sctrlHENFindFunction


#define PatchSyscall sctrlHENPatchSyscall

int sctrlSERstMiniConfig(VshConfig *config); // Reset Config
int sctrlSEGetMiniConfig(VshConfig *config);
int sctrlSESetMiniConfig(VshConfig *config);

void SetSpeed(int cpu, int bus);

//int sctrlKernelUncompress(u8 *dest, int destLen, const u8 *source, int sourceLen);

int sctrlIsHomebrewsRunLevel(void);
#endif