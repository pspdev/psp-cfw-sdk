#include <string.h>

#include <bootloadex.h>
#include <cfwmacros.h>
#include <pspbtcnf.h>
#include <rebootexconfig.h>
#include <systemctrl.h>
#include <systemctrl_se.h>


// ARK files
#define PATH_SYSTEMCTRL FLASH0_PATH "kd/m33_systemctrl.prx"
#define PATH_VSHCTRL FLASH0_PATH "kd/m33_vshctrl.prx"
#define PATH_GALAXY FLASH0_PATH "kd/m33_galaxy.prx"
#define PATH_MARCH33 FLASH0_PATH "kd/m33_march33.prx"
#define PATH_POPCORN FLASH0_PATH "kd/m33_popcorn.prx"
#define PATH_NIDRESOLVER FLASH0_PATH "kd/m33_nidresolver.prx"
#define PATH_IDCANAGER FLASH0_PATH "kd/m33_idcanager.prx"

// pspbtcnf patches

static int patch_bootconf_vsh(char *buffer, int length) {

    int newsize, result;

    result = length;

    newsize =
        AddPRX(buffer, "/kd/vshbridge.prx", PATH_VSHCTRL + sizeof(FLASH0_PATH) - 2, VSH_RUNLEVEL);
    if (newsize > 0) {
        result = newsize;
    }

    return result;
}

static int patch_bootconf_pops(char *buffer, int length) {
    int newsize, result;

    result = length;
    newsize = AddPRX(
        buffer, "/kd/usersystemlib.prx", PATH_POPCORN + sizeof(FLASH0_PATH) - 2, POPS_RUNLEVEL
    );

    if (newsize > 0) {
        result = newsize;
    }

    return result;
}

static struct BtcnfModuleAdd march33_add_mods[] = {
    {                         "/kd/mgr.prx",  "/kd/amctrl.prx",   GAME_RUNLEVEL},
    {PATH_MARCH33 + sizeof(FLASH0_PATH) - 2, "/kd/utility.prx",   GAME_RUNLEVEL},
    {PATH_MARCH33 + sizeof(FLASH0_PATH) - 2,   "/kd/isofs.prx", UMDEMU_RUNLEVEL},
    {                       "/kd/isofs.prx", "/kd/utility.prx",   GAME_RUNLEVEL},
};

static struct BtcnfModuleDel march33_del_mods[] = {
    {"/kd/mediaman.prx",   GAME_RUNLEVEL},
    {     "/kd/ata.prx",   GAME_RUNLEVEL},
    {  "/kd/umdman.prx",   GAME_RUNLEVEL},
    {"/kd/umdcache.prx",   GAME_RUNLEVEL},
    { "/kd/umd9660.prx",   GAME_RUNLEVEL},
    {  "/kd/np9660.prx", UMDEMU_RUNLEVEL},
};

u8 g_recovery_mode = 0;

static int patch_bootconf_march33(char *buffer, int length) {
    int newsize, result;

    result = length;

    for (int i = 0; i < NELEMS(march33_del_mods); ++i) {
        RemovePrx(buffer, march33_del_mods[i].prxname, march33_del_mods[i].flags);
    }

    for (int i = 0; i < NELEMS(march33_add_mods); ++i) {
        newsize = MovePrx(
            buffer, march33_add_mods[i].insertbefore, march33_add_mods[i].prxname,
            march33_add_mods[i].flags
        );

        if (newsize > 0) {
            result = newsize;
        }
    }

    return result;
}

static struct BtcnfModuleAdd vshumd_add_mods[] = {
    {                       "/kd/isofs.prx", "/kd/utility.prx", VSH_RUNLEVEL},
    {PATH_MARCH33 + sizeof(FLASH0_PATH) - 2, "/kd/chnnlsv.prx", VSH_RUNLEVEL},
};

static struct BtcnfModuleDel vshumd_del_mods[] = {
    {"/kd/mediaman.prx", VSH_RUNLEVEL},
    {     "/kd/ata.prx", VSH_RUNLEVEL},
    {  "/kd/umdman.prx", VSH_RUNLEVEL},
    { "/kd/umd9660.prx", VSH_RUNLEVEL},
};

static int patch_bootconf_vshumd(char *buffer, int length) {
    int newsize, result;

    result = length;

    for (int i = 0; i < NELEMS(vshumd_del_mods); ++i) {
        RemovePrx(buffer, vshumd_del_mods[i].prxname, vshumd_del_mods[i].flags);
    }

    for (int i = 0; i < NELEMS(vshumd_add_mods); ++i) {
        newsize = MovePrx(
            buffer, vshumd_add_mods[i].insertbefore, vshumd_add_mods[i].prxname,
            vshumd_add_mods[i].flags
        );

        if (newsize > 0) {
            result = newsize;
        }
    }

    return result;
}

static struct BtcnfModuleAdd updaterumd_add_mods[] = {
    {                       "/kd/isofs.prx", "/kd/utility.prx", UPDATER_RUNLEVEL},
    {PATH_MARCH33 + sizeof(FLASH0_PATH) - 2, "/kd/chnnlsv.prx", UPDATER_RUNLEVEL},
};

static struct BtcnfModuleDel updaterumd_del_mods[] = {
    {"/kd/mediaman.prx", UPDATER_RUNLEVEL},
    {     "/kd/ata.prx", UPDATER_RUNLEVEL},
    {  "/kd/umdman.prx", UPDATER_RUNLEVEL},
    { "/kd/umd9660.prx", UPDATER_RUNLEVEL},
};

static int patch_bootconf_updaterumd(char *buffer, int length) {
    int newsize, result;

    result = length;

    for (int i = 0; i < NELEMS(updaterumd_del_mods); ++i) {
        RemovePrx(buffer, updaterumd_del_mods[i].prxname, updaterumd_del_mods[i].flags);
    }

    for (int i = 0; i < NELEMS(updaterumd_add_mods); ++i) {
        newsize = MovePrx(
            buffer, updaterumd_add_mods[i].insertbefore, updaterumd_add_mods[i].prxname,
            updaterumd_add_mods[i].flags
        );

        if (newsize > 0) {
            result = newsize;
        }
    }

    return result;
}

int UnpackBootConfigM33PSP(char *buffer, int length) {
    int result = length;
    int newsize = 0;

    // Insert NID Resolver
    newsize =
        AddPRX(buffer, "/kd/init.prx", PATH_NIDRESOLVER + sizeof(FLASH0_PATH) - 2, 0x000000EF);
    if (newsize > 0) {
        result = newsize;
    }

    // Insert SystemControl
    newsize = AddPRX(
        buffer, PATH_NIDRESOLVER + sizeof(FLASH0_PATH) - 2,
        PATH_SYSTEMCTRL + sizeof(FLASH0_PATH) - 2, 0x000000EF
    );
    if (newsize > 0) {
        result = newsize;
    }

    // Insert VSHControl
    if (SearchPrx(buffer, "/vsh/module/vshmain.prx") >= 0) {
        newsize = patch_bootconf_vsh(buffer, result);
        if (newsize > 0) {
            result = newsize;
        }
    }

    // Insert Popcorn
    newsize = patch_bootconf_pops(buffer, result);
    if (newsize > 0) {
        result = newsize;
    }

    // initialize ARK reboot config
    if (ble_config->boot_type == TYPE_REBOOTEX) {
        RebootexConfigM33 *reboot_conf = (RebootexConfigM33 *)REBOOTEX_CONFIG;
        // copy rtm module information
        // memcpy(&ble_config->rtm_mod, &reboot_conf->rtm_mod, sizeof(ble_config->rtm_mod));

        // fix MODE_NP9660 (Galaxy driver no longer exists, redirect to either inferno or normal)
        if (reboot_conf->iso_mode == MODE_VSHUMD || reboot_conf->iso_mode == MODE_UPDATERUMD) {
            reboot_conf->iso_mode = MODE_UMD;
        } else if (reboot_conf->iso_mode == MODE_OE_LEGACY || reboot_conf->iso_mode == MODE_ME
                   || reboot_conf->iso_mode == MODE_INFERNO) {
            if (reboot_conf->iso_filename[0] == 0) {
                // no ISO -> normal mode
                reboot_conf->iso_mode = MODE_UMD;

            } else {
                // attempting to load an ISO with NP9660 is no longer possible, use inferno instead
                reboot_conf->iso_mode = MODE_MARCH33;
            }
        }

        // Configure boot mode
        switch (reboot_conf->iso_mode) {
            case MODE_ME:
            case MODE_INFERNO:
            case MODE_MARCH33:
            case MODE_OE_LEGACY:
                reboot_conf->iso_mode = MODE_MARCH33;
                newsize = patch_bootconf_march33(buffer, result);
                if (newsize > 0) {
                    result = newsize;
                }
                break;
            case MODE_RECOVERY:
                g_recovery_mode = 1;
                break;
            default:
                break;
        }
    }

    if (ble_config->boot_type == TYPE_PAYLOADEX && ble_config->boot_storage == MS_BOOT) {
        g_recovery_mode = 1; // enable recovery mode in DC
    }

    // disable fatms371 mod in recovery mode
    if (g_recovery_mode) {
        ble_config->extra_io.psp_io.use_fatms371 = 0;
    }

    return result;
}
