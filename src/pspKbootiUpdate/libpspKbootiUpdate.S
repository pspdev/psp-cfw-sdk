	.set noreorder

#include "pspimport.s"

// Build files
// libpspKbootiUpdate_XXXX.o

#ifdef F_libpspKbootiUpdate_0000
	IMPORT_START "kbooti_update",0x40090000
#endif
#ifdef F_libpspKbootiUpdate_0001
	IMPORT_FUNC  "kbooti_update",0x8B650F57,pspKbootiUpdateGetKbootiSize
#endif
#ifdef F_libpspKbootiUpdate_0002
	IMPORT_FUNC  "kbooti_update",0x2FBA6BE4,pspKbootiUpdateKbooti
#endif
#ifdef F_libpspKbootiUpdate_0003
	IMPORT_FUNC  "kbooti_update",0x32A8C95A,pspKbootiUpdateRestoreKbooti
#endif
