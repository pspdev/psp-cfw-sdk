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

int patch_bootconf_lme_recovery(char *buffer, int length)
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

int patch_bootconf_lme_isotope(char *buffer, int length)
{
    int result = length;
    int newsize;

    RemovePrx(buffer, "/kd/np9660.prx", UMDEMU_RUNLEVEL);
    newsize = AddPRX(buffer, "/kd/np9660.prx", "/kd/isotope.prx", UMDEMU_RUNLEVEL);
    
    if (newsize > 0) result = newsize;

    return result;
}

int patch_bootconf_lme_inferno(char *buffer, int length)
{
    int result = length;
    int newsize;

    RemovePrx(buffer, "/kd/np9660.prx", UMDEMU_RUNLEVEL);
    newsize = AddPRX(buffer, "/kd/np9660.prx", "/kd/inferno.prx", UMDEMU_RUNLEVEL);
    
    if (newsize > 0) result = newsize;

    return result;
}

int patch_bootconf_lme_np9660(char *buffer, int length)
{
    int result = length;
    int newsize;

    newsize = AddPRX(buffer, "/kd/np9660.prx", "/kd/pulsar.prx", UMDEMU_RUNLEVEL);
    
    if (newsize > 0) result = newsize;

    return result;
}

int UnpackBootConfigLMEPSP(char *buffer, int length)
{
    int result = length;
    int newsize;

    if (ble_config->boot_type == TYPE_REBOOTEX) {
        RebootexConfigLME *rebootex_param = (void *)REBOOTEX_CONFIG;
        switch (rebootex_param->reboot_index){
            case 2://NP9660
                newsize = patch_bootconf_lme_np9660(buffer, result);
                if (newsize > 0) result = newsize;
                break;
            case 1://M33
            case 3://ME	
                newsize = patch_bootconf_lme_isotope(buffer, result);
                if (newsize > 0) result = newsize;
                break;
            case 5://Inferno
                newsize = patch_bootconf_lme_inferno(buffer, result);
                if (newsize > 0) result = newsize;
                break;
            case 4: // recovery
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
