#include <string.h>

#include <systemctrl_se.h>

#include "bootloadex.h"
#include "bootloadex_ark.h"


int pspemuLfatOpenArkEPSP(BootFile* file)
{
    char* p = file->name;
    if (strcmp(p, "pspbtcnf.bin") == 0){
        p[2] = 'v'; // custom btcnf for PS Vita
        if (reboot_conf->iso_mode >= MODE_OE_LEGACY && reboot_conf->iso_mode <= MODE_ME){
            reboot_conf->iso_mode = MODE_INFERNO;
            p[5] = 'i'; // use inferno ISO mode (psvbtinf.bin)
        }
        // else use psvbtcnf.bin for np9660
    }
    return -1;
}
