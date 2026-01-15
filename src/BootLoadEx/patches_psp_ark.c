#include <string.h>

#include <ark.h>
#include <cfwmacros.h>
#include <systemctrl.h>
#include <systemctrl_se.h>
#include <pspbtcnf.h>
#include <bootloadex.h>
#include <bootloadex_ark.h>
#include <rebootexconfig.h>

// ARK files
#define PATH_SYSTEMCTRL FLASH0_PATH "kd/ark_systemctrl.prx"
#define PATH_PSPCOMPAT FLASH0_PATH "kd/ark_pspcompat.prx"
#define PATH_VITACOMPAT FLASH0_PATH "kd/ark_vitacompat.prx"
#define PATH_VITAPOPS FLASH0_PATH "kd/ark_vitapops.prx"
#define PATH_VSHCTRL FLASH0_PATH "kd/ark_vshctrl.prx"
#define PATH_STARGATE FLASH0_PATH "kd/ark_stargate.prx"
#define PATH_INFERNO FLASH0_PATH "kd/ark_inferno.prx"
#define PATH_POPCORN FLASH0_PATH "kd/ark_popcorn.prx"

// pspbtcnf patches

int patch_bootconf_vsh(char *buffer, int length)
{

    int newsize, result;

    result = length;

    newsize = AddPRX(buffer, "/kd/vshbridge.prx", PATH_VSHCTRL+sizeof(FLASH0_PATH)-2, VSH_RUNLEVEL );
    if (newsize > 0) result = newsize;

    newsize = AddPRX(buffer, "/kd/vshbridge_tool.prx", PATH_VSHCTRL+sizeof(FLASH0_PATH)-2, VSH_RUNLEVEL );
    if (newsize > 0){
        ark_config->exec_mode = PSP_TOOL;
        result = newsize;
    }

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

int UnpackBootConfigArkPSP(char *buffer, int length)
{

    int result = length;
    int newsize;

    // Insert SystemControl
    newsize = AddPRX(buffer, "/kd/init.prx", PATH_SYSTEMCTRL+sizeof(FLASH0_PATH)-2, 0x000000EF);
    if (newsize > 0) result = newsize;
    
    // Insert compat layer
    newsize = AddPRX(buffer, "/kd/init.prx", PATH_PSPCOMPAT+sizeof(FLASH0_PATH)-2, 0x000000EF);
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

    // initialize ARK reboot config
    initArkRebootConfig(ble_config);

    // Configure boot mode
    if (ble_config->boot_type == TYPE_REBOOTEX && IS_ARK_CONFIG(reboot_conf)){
        switch(reboot_conf->iso_mode) {
            default:
                break;
            case MODE_VSHUMD:
                newsize = patch_bootconf_vshumd(buffer, result);
                if (newsize > 0) result = newsize;
                break;
            case MODE_UPDATERUMD:
                newsize = patch_bootconf_updaterumd(buffer, result);
                if (newsize > 0) result = newsize;
                break;
            case MODE_ME:
            case MODE_INFERNO:
            case MODE_MARCH33:
            case MODE_OE_LEGACY:
                reboot_conf->iso_mode = MODE_INFERNO;
                newsize = patch_bootconf_inferno(buffer, result);
                if (newsize > 0) result = newsize;
                break;
        }
    }

    if (ble_config->boot_type == TYPE_PAYLOADEX && ble_config->boot_storage == MS_BOOT)
        ark_config->recovery = 1; // enable recovery mode in DC

    // disable fatms371 mod in recovery mode
    if (ark_config->recovery) ble_config->extra_io.psp_io.use_fatms371 = 0;
    
    return result;
}
