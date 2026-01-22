	.set noreorder

#include "pspimport.s"

// Build files
// AdrenalineCtrl_XXXX.o

#ifdef F_AdrenalineCtrl_0000
	IMPORT_START "AdrenalineCtrl",0x40090000
#endif
#ifdef F_AdrenalineCtrl_0001
	IMPORT_FUNC  "AdrenalineCtrl",0x586B8EB9,sctrlSendAdrenalineCmd
#endif
#ifdef F_AdrenalineCtrl_0002
	IMPORT_FUNC  "AdrenalineCtrl",0x05D8E209,sctrlGetUsbState
#endif
#ifdef F_AdrenalineCtrl_0003
	IMPORT_FUNC  "AdrenalineCtrl",0x80C0ED7B,sctrlStartUsb
#endif
#ifdef F_AdrenalineCtrl_0004
	IMPORT_FUNC  "AdrenalineCtrl",0x5FC12767,sctrlStopUsb
#endif
#ifdef F_AdrenalineCtrl_0005
	IMPORT_FUNC  "AdrenalineCtrl",0x053172F8,sctrlRebootDevice
#endif
#ifdef F_AdrenalineCtrl_0006
	IMPORT_FUNC  "AdrenalineCtrl",0xA93CFE9E,sctrlPentazeminConfigure
#endif
