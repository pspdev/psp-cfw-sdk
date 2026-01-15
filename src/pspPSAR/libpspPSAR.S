	.set noreorder

#include "pspimport.s"

// Build files
// libpspPSAR_XXXX.o

#ifdef F_libpspPSAR_0000
	IMPORT_START "pspPSAR",0x40090000
#endif
#ifdef F_libpspPSAR_0001
	IMPORT_FUNC  "pspPSAR",0x56C924E1,pspPSARInit
#endif
#ifdef F_libpspPSAR_0002
	IMPORT_FUNC  "pspPSAR",0x9C91DD9D,pspPSARGetNextFile
#endif
#ifdef F_libpspPSAR_0003
	IMPORT_FUNC  "pspPSAR",0xC907D012,pspPSARSetBufferPosition
#endif