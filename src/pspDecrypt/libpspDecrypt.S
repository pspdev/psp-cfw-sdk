	.set noreorder

#include "pspimport.s"

// Build files
// libpspDecrypt_XXXX.o

#ifdef F_libpspDecrypt_0000
	IMPORT_START "pspDecrypt",0x40090000
#endif
#ifdef F_libpspDecrypt_0001
	IMPORT_FUNC  "pspDecrypt",0xB081FD37,pspDecryptPRX
#endif
#ifdef F_libpspDecrypt_0002
	IMPORT_FUNC  "pspDecrypt",0x10360D7D,pspSignCheck
#endif
#ifdef F_libpspDecrypt_0003
	IMPORT_FUNC  "pspDecrypt",0xE1826CB7,pspDecryptIPL1
#endif
#ifdef F_libpspDecrypt_0004
	IMPORT_FUNC  "pspDecrypt",0x40ADB206,pspLinearizeIPL2
#endif
#ifdef F_libpspDecrypt_0005
	IMPORT_FUNC  "pspDecrypt",0xDCE318A9,pspDecryptIPL3
#endif
#ifdef F_libpspDecrypt_0006
	IMPORT_FUNC  "pspDecrypt",0x018C3EAC,pspDecompress
#endif
#ifdef F_libpspDecrypt_0007
	IMPORT_FUNC  "pspDecrypt",0xD31CB80A,pspDecryptTable
#endif
