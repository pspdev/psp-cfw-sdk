	.set noreorder

#include "pspimport.s"

// Build files
// libpspnodrm_helper_XXXX.o

#ifdef F_libpspnodrm_helper_0000
	IMPORT_START "NoDrm",0x00090000
#endif
#ifdef F_libpspnodrm_helper_0001
	IMPORT_FUNC  "NoDrm",0x29BCB468,nodrmBBMacGetKey
#endif
#ifdef F_libpspnodrm_helper_0002
	IMPORT_FUNC  "NoDrm",0x2CA7352D,nodrmGetEdatKey
#endif
#ifdef F_libpspnodrm_helper_0003
	IMPORT_FUNC  "NoDrm",0x906A478B,nodrmGetVersionKey
#endif
