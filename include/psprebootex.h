#ifndef _REBOOTEX_H_
#define _REBOOTEX_H_

#include <pspmacros.h>

#define REBOOT_TEXT (KERNEL_BASE + 0x600000) // reboot.bin load address
#define REBOOTEX_TEXT (KERNEL_BASE + 0xFC0000) // rebootex load address
#define BOOTCONFIG_TEMP_BUFFER 0x88FB0200
#define REBOOT_MODULE "/rtm.prx"
#define REBOOT150_TEXT (KERNEL_BASE + 0xc00000)
#define REBOOT150_SIZE 0x16d40
#define REBOOT150_COMP_SIZE 0xC60B
#define REBOOT661_COMP_SIZE 0x12E18
#define REBOOT_HEADER_SIZE 0x10
#define REBOOT150_HEADER 'r',  'e',  'b',  'o',  'o',  't',  '.',  'b',  'i',  'n',  0x00, 0x00, 0xFB, 0xC5, 0x00, 0x00
#define REBOOT661_HEADER 'r',  'e',  'b',  'o',  'o',  't',  '.',  'b',  'i',  'n',  0x00, 0x00, 0x08, 0x2E, 0x01, 0x00

#define REBOOT150_BUFFER \
u8 reboot150[REBOOT150_COMP_SIZE] = \
{ \
    REBOOT150_HEADER \
};

#define REBOOT661_BUFFER \
u8 reboot661[REBOOT661_COMP_SIZE] __attribute__((aligned(16))) = \
{ \
    REBOOT661_HEADER \
};

#endif