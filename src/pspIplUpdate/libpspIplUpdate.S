	.set noreorder

#include "pspimport.s"

// Build files
// libpspIplUpdate_XXXX.o

#ifdef F_libpspIplUpdate_0000
	IMPORT_START "pspIplUpdate",0x40090000
#endif
#ifdef F_libpspIplUpdate_0001
	IMPORT_FUNC  "pspIplUpdate",0xAD923E2F,pspIplUpdateGetIpl
#endif
#ifdef F_libpspIplUpdate_0002
	IMPORT_FUNC  "pspIplUpdate",0xF7EF8E3F,pspIplUpdateSetIpl
#endif
#ifdef F_libpspIplUpdate_0003
	IMPORT_FUNC  "pspIplUpdate",0x282EDFEC,pspIplUpdateClearIpl
#endif
