	.set noreorder

#include "pspimport.s"

// Build files
// MECtrl_XXXX.o

#ifdef F_MECtrl_0000
	IMPORT_START "MECtrl",0x40090000
#endif
#ifdef F_MECtrl_0001
	IMPORT_FUNC  "MECtrl",0xEA85C82C,sctrlSESetMiniConfig
#endif
#ifdef F_MECtrl_0002
	IMPORT_FUNC  "MECtrl",0x27A0CE8A,sctrlSESetMiniConfigEx
#endif
#ifdef F_MECtrl_0003
	IMPORT_FUNC  "MECtrl",0x0A2C56A2,sctrlSEGetMiniConfig
#endif
#ifdef F_MECtrl_0004
	IMPORT_FUNC  "MECtrl",0x1A0FB936,sctrlSEGetMiniConfigEx
#endif
#ifdef F_MECtrl_0005
	IMPORT_FUNC  "MECtrl",0xEDB7E6AC,sctrlSERstMiniConfig
#endif
#ifdef F_MECtrl_0006
	IMPORT_FUNC  "MECtrl",0x78AE7B1D,sctrlSERstMiniConfigEx
#endif
