	.set noreorder

#include "pspimport.s"

// Build files
// ScePaf_XXXX.o

#ifdef F_ScePaf_0000
	IMPORT_START "scePaf",0x40090011
#endif
#ifdef F_scePaf_0001
	IMPORT_FUNC  "scePaf",0xD8895EA5,fgetc
#endif
#ifdef F_scePaf_0002
	IMPORT_FUNC  "scePaf",0xDBD9AEE8,floorf
#endif
#ifdef F_scePaf_0003
	IMPORT_FUNC  "scePaf",0x6F9AEEA7,fopen
#endif
#ifdef F_scePaf_0004
	IMPORT_FUNC  "scePaf",0xC3A08340,fputc
#endif
#ifdef F_scePaf_0005
	IMPORT_FUNC  "scePaf",0x2D7A7961,fread
#endif
#ifdef F_scePaf_0006
	IMPORT_FUNC  "scePaf",0xDB1612F1,free
#endif
#ifdef F_scePaf_0007
	IMPORT_FUNC  "scePaf",0xC2470B3A,fseek
#endif
#ifdef F_scePaf_0008
	IMPORT_FUNC  "scePaf",0x6D7C4FD9,ftell
#endif
#ifdef F_scePaf_0009
	IMPORT_FUNC  "scePaf",0x1E443486,fwrite
#endif
#ifdef F_scePaf_0010
	IMPORT_FUNC  "scePaf",0xD8BDDE8E,logf
#endif
#ifdef F_scePaf_0011
	IMPORT_FUNC  "scePaf",0x2A7AC2A8,longjmp
#endif
#ifdef F_scePaf_0012
	IMPORT_FUNC  "scePaf",0x5E909060,malloc
#endif
#ifdef F_scePaf_0013
	IMPORT_FUNC  "scePaf",0x7C125884,memalign
#endif
#ifdef F_scePaf_0014
	IMPORT_FUNC  "scePaf",0x87D8F003,memchr
#endif
#ifdef F_scePaf_0015
	IMPORT_FUNC  "scePaf",0xB05D9677,memcmp
#endif
#ifdef F_scePaf_0016
	IMPORT_FUNC  "scePaf",0xB4652CFE,memcpy
#endif
#ifdef F_scePaf_0017
	IMPORT_FUNC  "scePaf",0x942204C1,memmove
#endif
#ifdef F_scePaf_0018
	IMPORT_FUNC  "scePaf",0xD9E2D6E1,memset
#endif
#ifdef F_scePaf_0019
	IMPORT_FUNC  "scePaf",0x22560E39,mtrim
#endif
#ifdef F_scePaf_0020
	IMPORT_FUNC  "scePaf",0xC8A758BB,powf
#endif
#ifdef F_scePaf_0021
	IMPORT_FUNC  "scePaf",0x4D3063AD,printf
#endif
#ifdef F_scePaf_0022
	IMPORT_FUNC  "scePaf",0x7DF486A4,qsort
#endif
#ifdef F_scePaf_0023
	IMPORT_FUNC  "scePaf",0x5C6EA8A9,rand
#endif
#ifdef F_scePaf_0024
	IMPORT_FUNC  "scePaf",0x48AB1935,realloc
#endif
#ifdef F_scePaf_0025
	IMPORT_FUNC  "scePaf",0x0AE51CB3,setjmp
#endif
#ifdef F_scePaf_0026
	IMPORT_FUNC  "scePaf",0x744387EA,sinf
#endif
#ifdef F_scePaf_0027
	IMPORT_FUNC  "scePaf",0x7B7133D5,snprintf
#endif
#ifdef F_scePaf_0028
	IMPORT_FUNC  "scePaf",0xA138A376,sprintf
#endif
#ifdef F_scePaf_0029
	IMPORT_FUNC  "scePaf",0xA9732653,sqrtf
#endif
#ifdef F_scePaf_0030
	IMPORT_FUNC  "scePaf",0x30AF7A24,srand
#endif
#ifdef F_scePaf_0031
	IMPORT_FUNC  "scePaf",0x2E0AB700,strcasecmp
#endif
#ifdef F_scePaf_0032
	IMPORT_FUNC  "scePaf",0x98BA1D0B,strcat
#endif
#ifdef F_scePaf_0033
	IMPORT_FUNC  "scePaf",0xC3B2D310,strchr
#endif
#ifdef F_scePaf_0034
	IMPORT_FUNC  "scePaf",0x4CF09BA2,strcmp
#endif
#ifdef F_scePaf_0035
	IMPORT_FUNC  "scePaf",0x726DFBA9,strcpy
#endif
#ifdef F_scePaf_0036
	IMPORT_FUNC  "scePaf",0xD7DCB972,strlen
#endif
#ifdef F_scePaf_0037
	IMPORT_FUNC  "scePaf",0x20787BCD,strncasecmp
#endif
#ifdef F_scePaf_0038
	IMPORT_FUNC  "scePaf",0x8166CA82,strncat
#endif
#ifdef F_scePaf_0039
	IMPORT_FUNC  "scePaf",0xE0B32AE8,strncmp
#endif
#ifdef F_scePaf_0040
	IMPORT_FUNC  "scePaf",0x706ABBFF,strncpy
#endif
#ifdef F_scePaf_0041
	IMPORT_FUNC  "scePaf",0x4CE9C8D7,strpbrk
#endif
#ifdef F_scePaf_0042
	IMPORT_FUNC  "scePaf",0x22420CC7,strrchr
#endif
#ifdef F_scePaf_0043
	IMPORT_FUNC  "scePaf",0x1FC6FD06,strstr
#endif
#ifdef F_scePaf_0044
	IMPORT_FUNC  "scePaf",0xBC27194E,strtok
#endif
#ifdef F_scePaf_0045
	IMPORT_FUNC  "scePaf",0x7E600551,strtok_r
#endif
#ifdef F_scePaf_0046
	IMPORT_FUNC  "scePaf",0x3C4BC2CD,strtol
#endif
#ifdef F_scePaf_0047
	IMPORT_FUNC  "scePaf",0xA4B8A4E3,strtoul
#endif
#ifdef F_scePaf_0048
	IMPORT_FUNC  "scePaf",0xC5C17E46,swprintf
#endif
#ifdef F_scePaf_0049
	IMPORT_FUNC  "scePaf",0xE4B1EA4F,tanf
#endif
#ifdef F_scePaf_0050
	IMPORT_FUNC  "scePaf",0xF9EA5AF4,tolower
#endif
#ifdef F_scePaf_0051
	IMPORT_FUNC  "scePaf",0x32AA333E,toupper
#endif
#ifdef F_scePaf_0052
	IMPORT_FUNC  "scePaf",0xD68F2EAA,vsnprintf
#endif
#ifdef F_scePaf_0053
	IMPORT_FUNC  "scePaf",0x806AE7E7,vsprintf
#endif
#ifdef F_scePaf_0054
	IMPORT_FUNC  "scePaf",0x672AD179,wcscasecmp
#endif
#ifdef F_scePaf_0055
	IMPORT_FUNC  "scePaf",0x73F0D607,wcschr
#endif
#ifdef F_scePaf_0056
	IMPORT_FUNC  "scePaf",0xCCC1E8F7,wcscmp
#endif
#ifdef F_scePaf_0057
	IMPORT_FUNC  "scePaf",0xD45DB202,wcscpy
#endif
#ifdef F_scePaf_0058
	IMPORT_FUNC  "scePaf",0xAF067FA2,wcslen
#endif
#ifdef F_scePaf_0059
	IMPORT_FUNC  "scePaf",0x418FB7C0,wcsncmp
#endif
#ifdef F_scePaf_0060
	IMPORT_FUNC  "scePaf",0x3B450CF1,wcsncpy
#endif
#ifdef F_scePaf_0061
	IMPORT_FUNC  "scePaf",0xE5219706,wcsrchr
#endif
#ifdef F_scePaf_0062
	IMPORT_FUNC  "scePaf",0x7C0006B7,wprintf
#endif

