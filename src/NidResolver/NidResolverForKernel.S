	.set noreorder

#include "pspimport.s"

// Build files
// NidResolverForKernel_0000.o NidResolverForKernel_0001.o NidResolverForKernel_0002.o NidResolverForKernel_0003.o 

#ifdef F_NidResolverForKernel_0000
	IMPORT_START "NidResolverForKernel",0x00090011
#endif
#ifdef F_NidResolverForKernel_0001
	IMPORT_FUNC  "NidResolverForKernel",0x2AB16906,FindLib
#endif
#ifdef F_NidResolverForKernel_0002
	IMPORT_FUNC  "NidResolverForKernel",0x59C1D1A7,FindNewNid
#endif
#ifdef F_NidResolverForKernel_0003
	IMPORT_FUNC  "NidResolverForKernel",0x6A5F76B5,sctrlHENRegisterLLEHandler
#endif
