	.set noreorder

#include "pspimport.s"

// Build files
// ScePaf_XXXX.o

#ifdef F_ScePafLibc_0000
	IMPORT_START "scePaf",0x00090000
#endif
#ifdef F_ScePafLibc_0001
	IMPORT_FUNC  "scePaf",0xF6C1E0E8,abs
#endif
#ifdef F_ScePafLibc_0002
	IMPORT_FUNC  "scePaf",0x318EEE19,acosf
#endif
#ifdef F_ScePafLibc_0003
	IMPORT_FUNC  "scePaf",0xB43BD048,atan2f
#endif
#ifdef F_ScePafLibc_0004
	IMPORT_FUNC  "scePaf",0x2300A4B5,atoi
#endif
#ifdef F_ScePafLibc_0005
	IMPORT_FUNC  "scePaf",0x7FB10989,atol
#endif
#ifdef F_ScePafLibc_0006
	IMPORT_FUNC  "scePaf",0x61F60E59,bcopy
#endif
#ifdef F_ScePafLibc_0007
	IMPORT_FUNC  "scePaf",0xCFCBBB65,bsearch
#endif
#ifdef F_ScePafLibc_0008
	IMPORT_FUNC  "scePaf",0x313D3025,bzero
#endif
#ifdef F_ScePafLibc_0009
	IMPORT_FUNC  "scePaf",0x533A9FB5,calloc
#endif
#ifdef F_ScePafLibc_0010
	IMPORT_FUNC  "scePaf",0xF9764170,ceilf
#endif
#ifdef F_ScePafLibc_0011
	IMPORT_FUNC  "scePaf",0xD12DC85F,cosf
#endif
#ifdef F_ScePafLibc_0012
	IMPORT_FUNC  "scePaf",0x14CA3815,fabsf
#endif
#ifdef F_ScePafLibc_0013
	IMPORT_FUNC  "scePaf",0x02A60EBD,fclose
#endif
#ifdef F_ScePafLibc_0014
	IMPORT_FUNC  "scePaf",0x14360185,feof
#endif
#ifdef F_ScePafLibc_0015
	IMPORT_FUNC  "scePaf",0xACAD5D85,ferror
#endif
#ifdef F_ScePafLibc_0016
	IMPORT_FUNC  "scePaf",0xAD8E4382,fflush
#endif
#ifdef F_ScePafLibc_0017
	IMPORT_FUNC  "scePaf",0xD8895EA5,fgetc
#endif
#ifdef F_ScePafLibc_0018
	IMPORT_FUNC  "scePaf",0xDBD9AEE8,floorf
#endif
#ifdef F_ScePafLibc_0019
	IMPORT_FUNC  "scePaf",0xB73A78AF,fopen
#endif
#ifdef F_ScePafLibc_0020
	IMPORT_FUNC  "scePaf",0xC3A08340,fputc
#endif
#ifdef F_ScePafLibc_0021
	IMPORT_FUNC  "scePaf",0x2D7A7961,fread
#endif
#ifdef F_ScePafLibc_0022
	IMPORT_FUNC  "scePaf",0x412B2F09,free
#endif
#ifdef F_ScePafLibc_0023
	IMPORT_FUNC  "scePaf",0xC2470B3A,fseek
#endif
#ifdef F_ScePafLibc_0024
	IMPORT_FUNC  "scePaf",0xACAD5D85,ftell
#endif
#ifdef F_ScePafLibc_0025
	IMPORT_FUNC  "scePaf",0x1E443486,fwrite
#endif
#ifdef F_ScePafLibc_0026
	IMPORT_FUNC  "scePaf",0xD8BDDE8E,logf
#endif
#ifdef F_ScePafLibc_0027
	IMPORT_FUNC  "scePaf",0x2A7AC2A8,longjmp
#endif
#ifdef F_ScePafLibc_0028
	IMPORT_FUNC  "scePaf",0xB9DDDCC8,malloc
#endif
#ifdef F_ScePafLibc_0029
	IMPORT_FUNC  "scePaf",0x0C2CD696,memalign
#endif
#ifdef F_ScePafLibc_0030
	IMPORT_FUNC  "scePaf",0x87D8F003,memchr
#endif
#ifdef F_ScePafLibc_0031
	IMPORT_FUNC  "scePaf",0xB05D9677,memcmp
#endif
#ifdef F_ScePafLibc_0032
	IMPORT_FUNC  "scePaf",0xB4652CFE,memcpy
#endif
#ifdef F_ScePafLibc_0033
	IMPORT_FUNC  "scePaf",0xF7C46E37,memmove
#endif
#ifdef F_ScePafLibc_0034
	IMPORT_FUNC  "scePaf",0xD9E2D6E1,memset
#endif
#ifdef F_ScePafLibc_0035
	IMPORT_FUNC  "scePaf",0xC8A758BB,powf
#endif
#ifdef F_ScePafLibc_0036
	IMPORT_FUNC  "scePaf",0x7DF486A4,qsort
#endif
#ifdef F_ScePafLibc_0037
	IMPORT_FUNC  "scePaf",0x5C6EA8A9,rand
#endif
#ifdef F_ScePafLibc_0038
	IMPORT_FUNC  "scePaf",0x48AB1935,realloc
#endif
#ifdef F_ScePafLibc_0039
	IMPORT_FUNC  "scePaf",0x0AE51CB3,setjmp
#endif
#ifdef F_ScePafLibc_0040
	IMPORT_FUNC  "scePaf",0x744387EA,sinf
#endif
#ifdef F_ScePafLibc_0041
	IMPORT_FUNC  "scePaf",0x7B7133D5,snprintf
#endif
#ifdef F_ScePafLibc_0042
	IMPORT_FUNC  "scePaf",0xA138A376,sprintf
#endif
#ifdef F_ScePafLibc_0043
	IMPORT_FUNC  "scePaf",0xA9732653,sqrtf
#endif
#ifdef F_ScePafLibc_0044
	IMPORT_FUNC  "scePaf",0x30AF7A24,srand
#endif
#ifdef F_ScePafLibc_0045
	IMPORT_FUNC  "scePaf",0x2E0AB700,strcasecmp
#endif
#ifdef F_ScePafLibc_0046
	IMPORT_FUNC  "scePaf",0x98BA1D0B,strcat
#endif
#ifdef F_ScePafLibc_0047
	IMPORT_FUNC  "scePaf",0xC3B2D310,strchr
#endif
#ifdef F_ScePafLibc_0048
	IMPORT_FUNC  "scePaf",0x4CF09BA2,strcmp
#endif
#ifdef F_ScePafLibc_0049
	IMPORT_FUNC  "scePaf",0x726DFBA9,strcpy
#endif
#ifdef F_ScePafLibc_0050
	IMPORT_FUNC  "scePaf",0xD7DCB972,strlen
#endif
#ifdef F_ScePafLibc_0051
	IMPORT_FUNC  "scePaf",0x20787BCD,strncasecmp
#endif
#ifdef F_ScePafLibc_0052
	IMPORT_FUNC  "scePaf",0x8166CA82,strncat
#endif
#ifdef F_ScePafLibc_0053
	IMPORT_FUNC  "scePaf",0xE0B32AE8,strncmp
#endif
#ifdef F_ScePafLibc_0054
	IMPORT_FUNC  "scePaf",0x706ABBFF,strncpy
#endif
#ifdef F_ScePafLibc_0055
	IMPORT_FUNC  "scePaf",0x4CE9C8D7,strpbrk
#endif
#ifdef F_ScePafLibc_0056
	IMPORT_FUNC  "scePaf",0x22420CC7,strrchr
#endif
#ifdef F_ScePafLibc_0057
	IMPORT_FUNC  "scePaf",0x1FC6FD06,strstr
#endif
#ifdef F_ScePafLibc_0058
	IMPORT_FUNC  "scePaf",0xBC27194E,strtok
#endif
#ifdef F_ScePafLibc_0059
	IMPORT_FUNC  "scePaf",0x7E600551,strtok_r
#endif
#ifdef F_ScePafLibc_0060
	IMPORT_FUNC  "scePaf",0x3C4BC2CD,strtol
#endif
#ifdef F_ScePafLibc_0061
	IMPORT_FUNC  "scePaf",0xA4B8A4E3,strtoul
#endif
#ifdef F_ScePafLibc_0062
	IMPORT_FUNC  "scePaf",0xC5C17E46,swprintf
#endif
#ifdef F_ScePafLibc_0063
	IMPORT_FUNC  "scePaf",0xE4B1EA4F,tanf
#endif
#ifdef F_ScePafLibc_0064
	IMPORT_FUNC  "scePaf",0xF9EA5AF4,tolower
#endif
#ifdef F_ScePafLibc_0065
	IMPORT_FUNC  "scePaf",0x32AA333E,toupper
#endif
#ifdef F_ScePafLibc_0066
	IMPORT_FUNC  "scePaf",0xD68F2EAA,vsnprintf
#endif
#ifdef F_ScePafLibc_0067
	IMPORT_FUNC  "scePaf",0x806AE7E7,vsprintf
#endif
#ifdef F_ScePafLibc_0068
	IMPORT_FUNC  "scePaf",0x672AD179,wcscasecmp
#endif
#ifdef F_ScePafLibc_0069
	IMPORT_FUNC  "scePaf",0x73F0D607,wcschr
#endif
#ifdef F_ScePafLibc_0070
	IMPORT_FUNC  "scePaf",0xCCC1E8F7,wcscmp
#endif
#ifdef F_ScePafLibc_0071
	IMPORT_FUNC  "scePaf",0xEC805E95,wcscpy
#endif
#ifdef F_ScePafLibc_0072
	IMPORT_FUNC  "scePaf",0xAF067FA2,wcslen
#endif
#ifdef F_ScePafLibc_0073
	IMPORT_FUNC  "scePaf",0x95692855,wcsncmp
#endif
#ifdef F_ScePafLibc_0074
	IMPORT_FUNC  "scePaf",0x3B450CF1,wcsncpy
#endif
#ifdef F_ScePafLibc_0075
	IMPORT_FUNC  "scePaf",0xC8C5BFD8,wcsrchr
#endif
#ifdef F_ScePafLibc_0076
	IMPORT_FUNC  "scePaf",0xD0A5385A,__assert
#endif
