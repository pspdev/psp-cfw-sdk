	.set noreorder

#include "pspimport.s"

#ifdef F_idsRegeneration_0000
	IMPORT_START "idsRegeneration",0x40090000
#endif
#ifdef F_idsRegeneration_0001
	IMPORT_FUNC  "idsRegeneration",0xBDE13E76,idsRegenerationSetup
#endif
#ifdef F_idsRegeneration_0002
	IMPORT_FUNC  "idsRegeneration",0xFEE3C55B,idsRegenerationGetIndex
#endif
#ifdef F_idsRegeneration_0003
	IMPORT_FUNC  "idsRegeneration",0x0B33639A,idsRegenerationGetHwConfigKeys
#endif
#ifdef F_idsRegeneration_0004
	IMPORT_FUNC  "idsRegeneration",0xFEA979A6,idsRegenerationGetMGKeys
#endif
#ifdef F_idsRegeneration_0005
	IMPORT_FUNC  "idsRegeneration",0xEE1AD992,idsRegenerationGetFactoryBadBlocksKey
#endif
#ifdef F_idsRegeneration_0006
	IMPORT_FUNC  "idsRegeneration",0x87A30D3A,idsRegenerationGetSerialKey
#endif
#ifdef F_idsRegeneration_0007
	IMPORT_FUNC  "idsRegeneration",0xE37CC2E6,idsRegenerationGetWlanKey
#endif
#ifdef F_idsRegeneration_0008
	IMPORT_FUNC  "idsRegeneration",0xC44FE956,idsRegenerationGetAudioVolumeSetupKey
#endif
#ifdef F_idsRegeneration_0009
	IMPORT_FUNC  "idsRegeneration",0xBC42FEED,idsRegenerationGetUsbKeys
#endif
#ifdef F_idsRegeneration_0010
	IMPORT_FUNC  "idsRegeneration",0x3F014928,idsRegenerationGetUnkKey140
#endif
#ifdef F_idsRegeneration_0011	
	IMPORT_FUNC  "idsRegeneration",0x8F7EE9C0,idsRegenerationGetMGKey40
#endif
#ifdef F_idsRegeneration_0012	
	IMPORT_FUNC  "idsRegeneration",0xB9156F27,idsRegenerationGetUnkKeys3X
#endif
#ifdef F_idsRegeneration_0013
	IMPORT_FUNC  "idsRegeneration",0xB417BCF0,idsRegenerationGetParentalLockKey
#endif
#ifdef F_idsRegeneration_0014
	IMPORT_FUNC  "idsRegeneration",0xFA2368E8,idsRegenerationGenerateFactoryFirmwareKey
#endif
#ifdef F_idsRegeneration_0015
	IMPORT_FUNC  "idsRegeneration",0x0EF8731D,idsRegenerationGetLCDKey
#endif
#ifdef F_idsRegeneration_0016
	IMPORT_FUNC  "idsRegeneration",0x4E95D36F,idsRegenerationGenerateCallibrationKey
#endif
#ifdef F_idsRegeneration_0017
	IMPORT_FUNC  "idsRegeneration",0xD7603D82,idsRegenerationGetUnkKeys5253
#endif
#ifdef F_idsRegeneration_0018
	IMPORT_FUNC  "idsRegeneration",0x6015A7CD,idsRegenerationGetDefaultXMBColorKey
#endif
#ifdef F_idsRegeneration_0019
	IMPORT_FUNC  "idsRegeneration",0xB79A6C46,idsRegenerationCreateCertificatesAndUMDKeys
#endif
