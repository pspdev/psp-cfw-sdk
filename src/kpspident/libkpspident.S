	.set noreorder

#include "pspimport.s"

// Build files
// libkpspident_XXXX.o

#ifdef F_libkpspident_0000
	IMPORT_START "kpspident",0x40090000
#endif
#ifdef F_libkpspident_0001
	IMPORT_FUNC  "kpspident",0x7EC5A957,sceSysconGetBaryonVersion
#endif
#ifdef F_libkpspident_0002
	IMPORT_FUNC  "kpspident",0xE7E87741,sceSysconGetPommelVersion
#endif
#ifdef F_libkpspident_0003
	IMPORT_FUNC  "kpspident",0xE2A5D1EE,sceSysregGetTachyonVersion
#endif
#ifdef F_libkpspident_0004
	IMPORT_FUNC  "kpspident",0xA27B1BA6,pspGetKirkVersion
#endif
#ifdef F_libkpspident_0005
	IMPORT_FUNC  "kpspident",0xFF2702F2,pspGetSpockVersion
#endif
