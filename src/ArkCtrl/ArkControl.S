	.set noreorder

#include "pspimport.s"

// Build files
// ArkCtrl_XXXX.o

#ifdef F_ArkCtrl_0000
	IMPORT_START "ArkCtrl",0x40090000
#endif
#ifdef F_ArkCtrl_0001
	IMPORT_FUNC  "ArkCtrl",0xB00B1E55,sctrlArkGetConfig
#endif
#ifdef F_ArkCtrl_0002
	IMPORT_FUNC  "ArkCtrl",0x8476E2F1,sctrlArkExitLauncher
#endif
