#include <string.h>

#include <ark.h>
#include <cfwmacros.h>
#include <systemctrl.h>
#include <systemctrl_se.h>
#include <bootloadex.h>
#include <pspbtcnf.h>
#include <rebootexconfig.h>

RebootexConfigARK* reboot_conf = (RebootexConfigARK*)REBOOTEX_CONFIG;
ARKConfig* ark_config = (ARKConfig*)ARK_CONFIG;

void initArkRebootConfig(BootLoadExConfig* ble_config){
    if (ble_config->boot_type == TYPE_REBOOTEX && IS_ARK_CONFIG(reboot_conf)){
        // copy rtm module information
        memcpy(&ble_config->rtm_mod, &reboot_conf->rtm_mod, sizeof(ble_config->rtm_mod));

        // fix MODE_NP9660 (Galaxy driver no longer exists, redirect to either inferno or normal)
        if (reboot_conf->iso_mode == MODE_NP9660){
            if (reboot_conf->iso_path[0] == 0){
                // no ISO -> normal mode
                reboot_conf->iso_mode = MODE_UMD;
            }
            else{
                // attempting to load an ISO with NP9660 is no longer possible, use inferno instead
                reboot_conf->iso_mode = MODE_INFERNO;
            }
        }
    }
}
