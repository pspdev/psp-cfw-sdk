	.set noreorder

#include "pspimport.s"

// Build files
// DcManager_XXXX.o

#ifdef F_DcManager_0000
	IMPORT_START "DcManager",0x40090000
#endif
#ifdef F_DcManager_0001
	IMPORT_FUNC  "DcManager",0xA22190CE,dcGetHardwareInfo
#endif
#ifdef F_DcManager_0002
	IMPORT_FUNC  "DcManager",0x3A3EA355,dcPatchModule
#endif
#ifdef F_DcManager_0003
	IMPORT_FUNC  "DcManager",0xD298BA53,dcPatchModuleString
#endif
#ifdef F_DcManager_0004
	IMPORT_FUNC  "DcManager",0x9C87A1C7,dcGetCancelMode
#endif
#ifdef F_DcManager_0005
	IMPORT_FUNC  "DcManager",0xF5161120,dcSetCancelMode
#endif
#ifdef F_DcManager_0006
	IMPORT_FUNC  "DcManager",0x39D91E83,dcLflashStartFatfmt
#endif
#ifdef F_DcManager_0007
	IMPORT_FUNC  "DcManager",0xA899D713,dcLflashStartFDisk
#endif
#ifdef F_DcManager_0008
	IMPORT_FUNC  "DcManager",0x741FFCFD,dcGetNandInfo
#endif
#ifdef F_DcManager_0009
	IMPORT_FUNC  "DcManager",0xEA3F4DE5,dcLockNand
#endif
#ifdef F_DcManager_0010
	IMPORT_FUNC  "DcManager",0x4A5FCC2F,dcUnlockNand
#endif
#ifdef F_DcManager_0011
	IMPORT_FUNC  "DcManager",0x7EB5614A,dcReadNandBlock
#endif
#ifdef F_DcManager_0012
	IMPORT_FUNC  "DcManager",0x504C82B4,dcWriteNandBlock
#endif
#ifdef F_DcManager_0013
	IMPORT_FUNC  "DcManager",0x7E9128B0,dcEraseNandBlock
#endif
#ifdef F_DcManager_0014
	IMPORT_FUNC  "DcManager",0xAD3509E5,dcRegisterPhysicalFormatCallback
#endif
#ifdef F_DcManager_0015
	IMPORT_FUNC  "DcManager",0x1A718513,dcUnregisterPhysicalFormatCallback
#endif
#ifdef F_DcManager_0016
	IMPORT_FUNC  "DcManager",0x48DDEA84,dcQueryRealMacAddress
#endif
#ifdef F_DcManager_0017
	IMPORT_FUNC  "DcManager",0x767A728E,dcIdStorageUnformat
#endif
#ifdef F_DcManager_0018
	IMPORT_FUNC  "DcManager",0xFE8EA2A0,dcIdStorageFormat
#endif
#ifdef F_DcManager_0019
	IMPORT_FUNC  "DcManager",0xFFAAC913,dcIdStorageCreateLeaf
#endif
#ifdef F_DcManager_0020
	IMPORT_FUNC  "DcManager",0xE5F8523D,dcIdStorageCreateAtomicLeaves
#endif
#ifdef F_DcManager_0021
	IMPORT_FUNC  "DcManager",0x127323A6,dcIdStorageReadLeaf
#endif
#ifdef F_DcManager_0022
	IMPORT_FUNC  "DcManager",0x549329DF,dcIdStorageWriteLeaf
#endif
#ifdef F_DcManager_0023
	IMPORT_FUNC  "DcManager",0x34F3F7FC,dcIdStorageFlush
#endif
#ifdef F_DcManager_0024
	IMPORT_FUNC  "DcManager",0xA6C4148A,dcSysconReceiveSetParam
#endif
#ifdef F_DcManager_0025
	IMPORT_FUNC  "DcManager",0x3534B9C1,dcKirkCmd
#endif
#ifdef F_DcManager_0026
	IMPORT_FUNC  "DcManager",0x109A36FC,SW
#endif
#ifdef F_DcManager_0027
	IMPORT_FUNC  "DcManager",0x4914B8D1,LW
#endif
