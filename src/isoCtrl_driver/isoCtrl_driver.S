	.set noreorder

#include "pspimport.s"

// Build files
// isoCtrl_driver_XXXX.o

#ifdef F_isoCtrl_driver_0000
	IMPORT_START "isoCtrl_driver",0x00090011
#endif
#ifdef F_isoCtrl_driver_0001
	IMPORT_FUNC  "isoCtrl_driver",0xD4FAB33F,isoGetTitleId
#endif
#ifdef F_isoCtrl_driver_0002
	IMPORT_FUNC  "isoCtrl_driver",0xFAEC97D6,isoSetUmdDelay
#endif
#ifdef F_isoCtrl_driver_0003
	IMPORT_FUNC  "isoCtrl_driver",0x3F83B110,isoReadUmdFile
#endif
#ifdef F_isoCtrl_driver_0004
	IMPORT_FUNC  "isoCtrl_driver",0x2830271E,isoSetUmdFile
#endif
#ifdef F_isoCtrl_driver_0005
	IMPORT_FUNC  "isoCtrl_driver",0xCA44FFAD,isoGetUmdFile
#endif
#ifdef F_isoCtrl_driver_0006
	IMPORT_FUNC  "isoCtrl_driver",0xB0B73A40,isoReopenUmdFile
#endif
#ifdef F_isoCtrl_driver_0007
	IMPORT_FUNC  "isoCtrl_driver",0xBBF7527A,isoSwapUmdFile
#endif
