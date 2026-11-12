#include <string.h>

#include <systemctrl_ark.h>
#include <cfwmacros.h>
#include <systemctrl.h>
#include <systemctrl_se.h>
#include <pspbtcnf.h>
#include <bootloadex.h>
#include <rebootexconfig.h>


int lme_recovery_mode = 0;

void BtcnfPathHandlerLME(char* path){
    path[9] = 'j'; // pspbtjnf
}

static int patch_bootconf_lme_recovery(char *buffer, int length)
{
    int result = length;
    int newsize;

    newsize = AddPRX(buffer, "/kd/usersystemlib.prx", "/kd/usbstorms.prx", VSH_RUNLEVEL);
    if (newsize > 0) result = newsize;
    RemovePrx(buffer, "/kd/usersystemlib.prx", VSH_RUNLEVEL);

    newsize = AddPRX(buffer, "/kd/libatrac3plus.prx", "/kd/usbstorboot.prx", VSH_RUNLEVEL);
    if (newsize > 0) result = newsize;
    RemovePrx(buffer, "/kd/libatrac3plus.prx", VSH_RUNLEVEL);

    newsize = AddPRX(buffer, "/kd/mediasync.prx", "/kd/usbstor.prx", VSH_RUNLEVEL);
    if (newsize > 0) result = newsize;
    RemovePrx(buffer, "/kd/mediasync.prx", VSH_RUNLEVEL);

    newsize = AddPRX(buffer, "/kd/vshctrl_02g.prx", "/kd/usbstormgr.prx", VSH_RUNLEVEL);
    if (newsize > 0) result = newsize;
    RemovePrx(buffer, "/kd/vshctrl_02g.prx", VSH_RUNLEVEL);

    newsize = AddPRX(buffer, "/vsh/module/paf.prx", "/kd/usbdev.prx", VSH_RUNLEVEL);
    if (newsize > 0) result = newsize;
    RemovePrx(buffer, "/vsh/module/paf.prx", VSH_RUNLEVEL);

    newsize = AddPRX(buffer, "/vsh/module/common_gui.prx", "/kd/lflash_fatfmt.prx", VSH_RUNLEVEL);
    if (newsize > 0) result = newsize;
    RemovePrx(buffer, "/vsh/module/common_gui.prx", VSH_RUNLEVEL);

    newsize = AddPRX(buffer, "/vsh/module/common_util.prx", "/kd/usersystemlib.prx", VSH_RUNLEVEL);
    if (newsize > 0) result = newsize;
    RemovePrx(buffer, "/vsh/module/common_util.prx", VSH_RUNLEVEL);
    
    newsize = AddPRX(buffer, "/vsh/module/vshmain.prx", "/vsh/module/recovery.prx", VSH_RUNLEVEL);
    if (newsize > 0) result = newsize;
    RemovePrx(buffer, "/vsh/module/vshmain.prx", VSH_RUNLEVEL);
    
    if (psp_model == PSP_GO)
    {
        newsize = AddPRX(buffer, "/vsh/module/mcore.prx", "/kd/usbstoreflash.prx", VSH_RUNLEVEL);
        if (newsize > 0) result = newsize;
        RemovePrx(buffer, "/vsh/module/mcore.prx", VSH_RUNLEVEL);
    }
    return result;
}

static void patch_bootconf_lme_runlevels(char *buffer)
{
    _btcnf_header *header = (_btcnf_header *)buffer;

    if (header->signature != BTCNF_MAGIC || header->nmodules <= 0) {
        return;
    }

    _btcnf_module *module = (_btcnf_module *)(buffer + header->modulestart);
    for (int i = 0; i < header->nmodules; i++) {
        if (module[i].flags & UMDEMU_RUNLEVEL) {
            module[i].flags |= GAME_RUNLEVEL;
        } else {
            module[i].flags &= ~GAME_RUNLEVEL;
        }
    }
}

static int patch_bootconf_lme_iso(char *buffer, int length, const char* driver)
{
    int result = length;
    int newsize;

    patch_bootconf_lme_runlevels(buffer);
    newsize = AddPRX(buffer, "/kd/np9660.prx", driver, UMDEMU_RUNLEVEL | GAME_RUNLEVEL);
    
    if (newsize > 0) result = newsize;

    return result;
}

int UnpackBootConfigLMEPSP(char *buffer, int length)
{
    int result = length;
    int newsize;

    if (ble_config->boot_type == TYPE_REBOOTEX) {
        RebootexConfigLME *rebootex_param = (void *)REBOOTEX_CONFIG;
        
        ble_config->rtm_mod.before = rebootex_param->on_reboot_after;
        ble_config->rtm_mod.buffer = rebootex_param->on_reboot_buf;
        ble_config->rtm_mod.size = rebootex_param->on_reboot_size;
        ble_config->rtm_mod.flags = rebootex_param->on_reboot_flag;

        switch (rebootex_param->reboot_index){
            case MODE_NP9660:
                newsize = patch_bootconf_lme_iso(buffer, result, "/kd/pulsar.prx");
                if (newsize > 0) result = newsize;
                break;
            case MODE_MARCH33:
                newsize = patch_bootconf_lme_iso(buffer, result, "/kd/dax9660.prx");
                if (newsize > 0) result = newsize;
                break;
            case MODE_ME:
                newsize = patch_bootconf_lme_iso(buffer, result, "/kd/isotope.prx");
                if (newsize > 0) result = newsize;
                break;
            case MODE_INFERNO:
                newsize = patch_bootconf_lme_iso(buffer, result, "/kd/inferno.prx");
                if (newsize > 0) result = newsize;
                break;
            case MODE_RECOVERY:
                lme_recovery_mode = 1;
                break;
        }
    }

    if (lme_recovery_mode){
        newsize = patch_bootconf_lme_recovery(buffer, result);
        if (newsize > 0) result = newsize;
    }

    return result;
}
