	.set noreorder

#include "pspimport.s"

#ifdef F_inferno_driver_0000
	IMPORT_START "inferno_driver",0x00090000
#endif
#ifdef F_inferno_driver_0001
	IMPORT_FUNC  "inferno_driver",0xCF8299BE,infernoSetDiscType
#endif
#ifdef F_inferno_driver_0002
	IMPORT_FUNC  "inferno_driver",0xC0736FD6,infernoCacheSetPolicy
#endif
#ifdef F_inferno_driver_0003
	IMPORT_FUNC  "inferno_driver",0x8CDE7F95,infernoCacheInit
#endif
#ifdef F_inferno_driver_0004
	IMPORT_FUNC  "inferno_driver",0xB6522E93,infernoSetUmdDelay
#endif
#ifdef F_inferno_driver_0005
	IMPORT_FUNC  "inferno_driver",0xB573209C,infernoIsoRead
#endif
