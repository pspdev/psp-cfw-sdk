#ifndef _BOOTLOADEX_ARK_H_
#define _BOOTLOADEX_ARK_H_

#include <systemctrl_ark.h>
#include <rebootexconfig.h>

// ARK specific functions
void initArkRebootConfig(BootLoadExConfig*);
int UnpackBootConfigArkPSP(char *buffer, int length);

#endif
