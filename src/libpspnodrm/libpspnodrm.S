	.set noreorder

#include "pspimport.s"

// Build files
// libpspnodrm_XXXX.o

#ifdef F_libpspnodrm_0000
	IMPORT_START "NoDrm",0x00090000
#endif
#ifdef F_libpspnodrm_0001
	IMPORT_FUNC  "NoDrm",0x92314D53,sctrlNoDrmBBMacGetKey
#endif
#ifdef F_libpspnodrm_0002
	IMPORT_FUNC  "NoDrm",0x7AE49CDF,sctrlNoDrmGetEdatKey
#endif
#ifdef F_libpspnodrm_0003
	IMPORT_FUNC  "NoDrm",0x100D6B84,sctrlNoDrmGetVersionKey
#endif
