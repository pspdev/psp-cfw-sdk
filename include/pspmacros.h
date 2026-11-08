#ifndef PSP_MACROS_H
#define PSP_MACROS_H

// magic numbers
#define PBP_MAGIC 0x50425000
#define ELF_MAGIC 0x464C457F
#define PSP_MAGIC 0x5053507E
#define BTCNF_MAGIC 0x0F803001
#define SFO_MAGIC 0x46535000

// Different firmware versions
#define FW_661 0x06060110
#define FW_660 0x06060010
#define FW_150 0x01050001

#define FLASH0_PATH "flash0:/"
#define FLASH1_PATH "flash1:/"
#define USER_BASE 0x08800000 // user partition (p2)
#define KERNEL_BASE 0x88000000 // kernel partition (p1)
#define GAME_TEXT (USER_BASE + 0x4000) // game's main elf load address
#define SYSMEM_TEXT KERNEL_BASE // sysmem.prx load address (start of kernel ram)
#define EXTRA_RAM 0x8A000000 // extra RAM (on 2k+ or vita)
#define VITA_FLASH_SONY 0x8B000000 // flash ramfs on vita
#define BOOT_KEY_BUFFER (KERNEL_BASE + 0xFB0000) // controller input in payloadex (cIPL)
#define USER_SIZE (24 * 1024 * 1024) // user partition size
#define KERNEL_SIZE (4 * 1024 * 1024) // kernel partition size
#define VITA_FLASH_SIZE 0x01000000 // vita flash ramfs size
#define EXTRA_RAM_SIZE (32 * 1024 * 1024) // size of extra ram (2k+)
#define MAX_HIGH_MEMSIZE 55 // max ram that can be given to user

#endif