#include <string.h>

#include <systemctrl_ark.h>
#include <cfwmacros.h>
#include <systemctrl.h>
#include <systemctrl_se.h>
#include <pspbtcnf.h>
#include <bootloadex.h>
#include <rebootexconfig.h>


// PRO files
#define PATH_SYSTEMCTRL FLASH0_PATH "kd/_systemctrl.prx"
#define PATH_VSHCTRL FLASH0_PATH "kd/_vshctrl.prx"
#define PATH_STARGATE FLASH0_PATH "kd/_stargate.prx"
#define PATH_GALAXY FLASH0_PATH "kd/_galaxy.prx"
#define PATH_MARCH33 FLASH0_PATH "kd/_march33.prx"
#define PATH_INFERNO FLASH0_PATH "kd/_inferno.prx"
#define PATH_POPCORN FLASH0_PATH "kd/_popcorn.prx"
#define PATH_RECOVERY FLASH0_PATH "vsh/module/_recovery.prx"


int pro_recovery_mode = 0;

// pspbtcnf patches
int patch_bootconf_vsh(char *buffer, int length)
{
    int newsize, result;

    result = length;

    newsize = AddPRX(buffer, "/kd/vshbridge.prx", PATH_VSHCTRL+sizeof(FLASH0_PATH)-2, VSH_RUNLEVEL );
    if (newsize > 0) result = newsize;

    return result;
}

int patch_bootconf_pops(char *buffer, int length)
{
    int newsize, result;

    result = length;
    newsize = AddPRX(buffer, "/kd/usersystemlib.prx", PATH_POPCORN+sizeof(FLASH0_PATH)-2, POPS_RUNLEVEL);

    if (newsize > 0) result = newsize;

    return result;
}

struct add_module {
    char *prxname;
    char *insertbefore;
    u32 flags;
};

struct del_module {
    char *prxname;
    u32 flags;
};

static struct add_module np9660_add_mods[] = {
	{ "/kd/mgr.prx", "/kd/amctrl.prx", GAME_RUNLEVEL },
	{ "/kd/npdrm.prx", "/kd/iofilemgr_dnas.prx", GAME_RUNLEVEL },
	{ PATH_GALAXY+sizeof(FLASH0_PATH)-2, "/kd/np9660.prx", UMDEMU_RUNLEVEL },
	{ PATH_GALAXY+sizeof(FLASH0_PATH)-2, "/kd/utility.prx", GAME_RUNLEVEL },
	{ "/kd/np9660.prx", "/kd/utility.prx", GAME_RUNLEVEL },
	{ "/kd/isofs.prx", "/kd/utility.prx", GAME_RUNLEVEL },
};

static struct del_module np9660_del_mods[] = {
	{ "/kd/mediaman.prx", GAME_RUNLEVEL },
	{ "/kd/ata.prx", GAME_RUNLEVEL },
	{ "/kd/umdman.prx", GAME_RUNLEVEL },
	{ "/kd/umdcache.prx", GAME_RUNLEVEL },
	{ "/kd/umd9660.prx", GAME_RUNLEVEL },
};

int patch_bootconf_np9660(char *buffer, int length)
{
	int newsize, result, ret;

	result = length;

	int i; for(i=0; i<NELEMS(np9660_del_mods); ++i) {
		RemovePrx(buffer, np9660_del_mods[i].prxname, np9660_del_mods[i].flags);
	}

	for(i=0; i<NELEMS(np9660_add_mods); ++i) {
		newsize = MovePrx(buffer, np9660_add_mods[i].insertbefore, np9660_add_mods[i].prxname, np9660_add_mods[i].flags);

		if (newsize > 0) result = newsize;
	}

	return result;
}

static struct add_module march33_add_mods[] = {
	{ "/kd/mgr.prx", "/kd/amctrl.prx", GAME_RUNLEVEL },
	{ PATH_MARCH33+sizeof(FLASH0_PATH)-2, "/kd/utility.prx", GAME_RUNLEVEL },
	{ PATH_MARCH33+sizeof(FLASH0_PATH)-2, "/kd/isofs.prx", UMDEMU_RUNLEVEL },
	{ "/kd/isofs.prx", "/kd/utility.prx", GAME_RUNLEVEL },
};

static struct del_module march33_del_mods[] = {
	{ "/kd/mediaman.prx", GAME_RUNLEVEL },
	{ "/kd/ata.prx", GAME_RUNLEVEL },
	{ "/kd/umdman.prx", GAME_RUNLEVEL },
	{ "/kd/umdcache.prx", GAME_RUNLEVEL },
	{ "/kd/umd9660.prx", GAME_RUNLEVEL },
	{ "/kd/np9660.prx", UMDEMU_RUNLEVEL },
};

int patch_bootconf_march33(char *buffer, int length)
{
	int newsize, result, ret;

	result = length;

	int i; for(i=0; i<NELEMS(march33_del_mods); ++i) {
		RemovePrx(buffer, march33_del_mods[i].prxname, march33_del_mods[i].flags);
	}

	for(i=0; i<NELEMS(march33_add_mods); ++i) {
		newsize = MovePrx(buffer, march33_add_mods[i].insertbefore, march33_add_mods[i].prxname, march33_add_mods[i].flags);

		if (newsize > 0) result = newsize;
	}

	return result;
}

static struct add_module inferno_add_mods[] = {
    { "/kd/mgr.prx", "/kd/amctrl.prx", GAME_RUNLEVEL },
    { PATH_INFERNO+sizeof(FLASH0_PATH)-2, "/kd/utility.prx", GAME_RUNLEVEL },
    { PATH_INFERNO+sizeof(FLASH0_PATH)-2, "/kd/isofs.prx", UMDEMU_RUNLEVEL },
    { "/kd/isofs.prx", "/kd/utility.prx", GAME_RUNLEVEL },
};

static struct del_module inferno_del_mods[] = {
    { "/kd/mediaman.prx", GAME_RUNLEVEL },
    { "/kd/ata.prx", GAME_RUNLEVEL },
    { "/kd/umdman.prx", GAME_RUNLEVEL },
    { "/kd/umdcache.prx", GAME_RUNLEVEL },
    { "/kd/umd9660.prx", GAME_RUNLEVEL },
    { "/kd/np9660.prx", UMDEMU_RUNLEVEL },
};

int patch_bootconf_inferno(char *buffer, int length)
{
    int newsize, result;

    result = length;

    int i; for(i=0; i<NELEMS(inferno_del_mods); ++i) {
        RemovePrx(buffer, inferno_del_mods[i].prxname, inferno_del_mods[i].flags);
    }

    for(i=0; i<NELEMS(inferno_add_mods); ++i) {
        newsize = MovePrx(buffer, inferno_add_mods[i].insertbefore, inferno_add_mods[i].prxname, inferno_add_mods[i].flags);

        if (newsize > 0) result = newsize;
    }

    return result;
}

static struct add_module vshumd_add_mods[] = {
    { "/kd/isofs.prx", "/kd/utility.prx", VSH_RUNLEVEL },
    { PATH_INFERNO+sizeof(FLASH0_PATH)-2, "/kd/chnnlsv.prx", VSH_RUNLEVEL },
};

static struct del_module vshumd_del_mods[] = {
    { "/kd/mediaman.prx", VSH_RUNLEVEL },
    { "/kd/ata.prx", VSH_RUNLEVEL },
    { "/kd/umdman.prx", VSH_RUNLEVEL },
    { "/kd/umd9660.prx", VSH_RUNLEVEL },
};

int patch_bootconf_vshumd(char *buffer, int length)
{
    int newsize, result;

    result = length;

    int i; for(i=0; i<NELEMS(vshumd_del_mods); ++i) {
        RemovePrx(buffer, vshumd_del_mods[i].prxname, vshumd_del_mods[i].flags);
    }

    for(i=0; i<NELEMS(vshumd_add_mods); ++i) {
        newsize = MovePrx(buffer, vshumd_add_mods[i].insertbefore, vshumd_add_mods[i].prxname, vshumd_add_mods[i].flags);

        if (newsize > 0) result = newsize;
    }

    return result;
}

static struct add_module updaterumd_add_mods[] = {
    { "/kd/isofs.prx", "/kd/utility.prx", UPDATER_RUNLEVEL },
    { PATH_INFERNO+sizeof(FLASH0_PATH)-2, "/kd/chnnlsv.prx", UPDATER_RUNLEVEL },
};

static struct del_module updaterumd_del_mods[] = {
    { "/kd/mediaman.prx", UPDATER_RUNLEVEL },
    { "/kd/ata.prx", UPDATER_RUNLEVEL },
    { "/kd/umdman.prx", UPDATER_RUNLEVEL },
    { "/kd/umd9660.prx", UPDATER_RUNLEVEL },
};

int patch_bootconf_updaterumd(char *buffer, int length)
{
    int newsize, result;

    result = length;

    int i; for(i=0; i<NELEMS(updaterumd_del_mods); ++i) {
        RemovePrx(buffer, updaterumd_del_mods[i].prxname, updaterumd_del_mods[i].flags);
    }

    for(i=0; i<NELEMS(updaterumd_add_mods); ++i) {
        newsize = MovePrx(buffer, updaterumd_add_mods[i].insertbefore, updaterumd_add_mods[i].prxname, updaterumd_add_mods[i].flags);

        if (newsize > 0) result = newsize;
    }

    return result;
}

int UnpackBootConfigPROPSP(char *buffer, int length)
{
    int result = length;
    int newsize;

    // Insert SystemControl
    newsize = AddPRX(buffer, "/kd/init.prx", PATH_SYSTEMCTRL+sizeof(FLASH0_PATH)-2, 0x000000EF);
    if (newsize > 0) result = newsize;

    // Insert Stargate No-DRM Engine
    newsize = AddPRX(buffer, "/kd/me_wrapper.prx", PATH_STARGATE+sizeof(FLASH0_PATH)-2, GAME_RUNLEVEL | UMDEMU_RUNLEVEL);
    if (newsize > 0) result = newsize;

    // Insert VSHControl
    if (SearchPrx(buffer, "/vsh/module/vshmain.prx") >= 0) {
        newsize = patch_bootconf_vsh(buffer, result);
        if (newsize > 0) result = newsize;
    }

    // Insert Popcorn
    newsize = patch_bootconf_pops(buffer, result);
    if (newsize > 0) result = newsize;

    // Configure boot mode
    if (ble_config->boot_type == TYPE_REBOOTEX) {
        RebootexConfigPRO *reboot_conf = (void *)REBOOTEX_CONFIG;
        if (reboot_conf->recovery_mode) pro_recovery_mode = 1;
        switch(reboot_conf->iso_mode) {
            case MODE_VSHUMD:
                newsize = patch_bootconf_vshumd(buffer, result);
                if (newsize > 0) result = newsize;
                break;
            case MODE_UPDATERUMD:
                newsize = patch_bootconf_updaterumd(buffer, result);
                if (newsize > 0) result = newsize;
                break;
            case MODE_NP9660:
                newsize = patch_bootconf_np9660(buffer, length);
                if (newsize > 0) result = newsize;
                break;
            case MODE_MARCH33:
                newsize = patch_bootconf_march33(buffer, length);
			    if (newsize > 0) result = newsize;
			    break;
            case MODE_ME:
            case MODE_INFERNO:
            case MODE_OE_LEGACY:
                newsize = patch_bootconf_inferno(buffer, result);
                if (newsize > 0) result = newsize;
                break;
        }
    }

    if (pro_recovery_mode){
        RemovePrx(buffer, "/vsh/module/vshmain.prx", VSH_RUNLEVEL);
        newsize = AddPRX(buffer, "/vsh/module/vshmain.prx", PATH_RECOVERY+sizeof(FLASH0_PATH)-2, VSH_RUNLEVEL);
        if (newsize > 0) result = newsize;
    }

    return result;
}
