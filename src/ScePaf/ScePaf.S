	.set noreorder

#include "pspimport.s"

// Build files
// ScePaf_XXXX.o

#ifdef F_ScePaf_0000
	IMPORT_START "scePaf",0x40090011
#endif
#ifdef F_ScePaf_0001
	IMPORT_FUNC  "scePaf",0xAF067FA2,wcslen
#endif
#ifdef F_ScePaf_0002
	IMPORT_FUNC  "scePaf",0xB4652CFE,memcpy
#endif
#ifdef F_ScePaf_0003
	IMPORT_FUNC  "scePaf",0xD9E2D6E1,memset
#endif
#ifdef F_ScePaf_0004
	IMPORT_FUNC  "scePaf",0xD7DCB972,strlen
#endif
#ifdef F_ScePaf_0005
	IMPORT_FUNC  "scePaf",0x98BA1D0B,strcat
#endif
#ifdef F_ScePaf_0006
	IMPORT_FUNC  "scePaf",0x726DFBA9,strcpy
#endif
#ifdef F_ScePaf_0007
	IMPORT_FUNC  "scePaf",0x706ABBFF,strncpy
#endif
#ifdef F_ScePaf_0008
	IMPORT_FUNC  "scePaf",0x4CF09BA2,strcmp
#endif
#ifdef F_ScePaf_0009
	IMPORT_FUNC  "scePaf",0xE0B32AE8,strncmp
#endif
#ifdef F_ScePaf_0010
	IMPORT_FUNC  "scePaf",0xC3B2D310,strchr
#endif
#ifdef F_ScePaf_0011
	IMPORT_FUNC  "scePaf",0x22420CC7,strrchr
#endif
#ifdef F_ScePaf_0012
	IMPORT_FUNC  "scePaf",0x4CE9C8D7,strpbrk
#endif
#ifdef F_ScePaf_0013
	IMPORT_FUNC  "scePaf",0xA4B8A4E3,strtoul
#endif
#ifdef F_ScePaf_0014
	IMPORT_FUNC  "scePaf",0xA138A376,sprintf
#endif
#ifdef F_ScePaf_0015
	IMPORT_FUNC  "scePaf",0x7B7133D5,snprintf
#endif
#ifdef F_ScePaf_0016
	IMPORT_FUNC  "scePaf",0x5E909060,malloc
#endif
#ifdef F_ScePaf_0017
	IMPORT_FUNC  "scePaf",0xDB1612F1,free
#endif
