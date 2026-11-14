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
#define FW_639 0x06030910
#define FW_635 0x06030510
#define FW_620 0x06020010
#define FW_610 0x06010010
#define FW_600 0x06000010
#define FW_551 0x05050110
#define FW_550 0x05050010
#define FW_503 0x05000310
#define FW_501 0x05000110
#define FW_500 0x05000010
#define FW_401 0x04000110
#define FW_396 0x03090610
#define FW_395 0x03090510
#define FW_393 0x03090310
#define FW_390 0x03090010
#define FW_380 0x03080010
#define FW_372 0x03070210
#define FW_371 0x03070110
#define FW_352 0x03050210
#define FW_351 0x03050110
#define FW_350 0x03050010
#define FW_340 0x03040010
#define FW_330 0x03030010
#define FW_311 0x03010110
#define FW_310 0x03010010
#define FW_303 0x03000310
#define FW_302 0x03000210
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