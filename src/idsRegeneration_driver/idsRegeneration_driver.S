	.set noreorder

#include "pspimport.s"

#ifdef F_idsRegeneration_driver_0000
	IMPORT_START "idsRegeneration_driver",0x00090000
#endif
#ifdef F_idsRegeneration_driver_0001
	IMPORT_FUNC  "idsRegeneration_driver",0xBDE13E76,idsRegenerationSetup
#endif
#ifdef F_idsRegeneration_driver_0002
	IMPORT_FUNC  "idsRegeneration_driver",0xFEE3C55B,idsRegenerationGetIndex
#endif
#ifdef F_idsRegeneration_driver_0003
	IMPORT_FUNC  "idsRegeneration_driver",0x0B33639A,idsRegenerationGetHwConfigKeys
#endif
#ifdef F_idsRegeneration_driver_0004
	IMPORT_FUNC  "idsRegeneration_driver",0xFEA979A6,idsRegenerationGetMGKeys
#endif
#ifdef F_idsRegeneration_driver_0005
	IMPORT_FUNC  "idsRegeneration_driver",0xEE1AD992,idsRegenerationGetFactoryBadBlocksKey
#endif
#ifdef F_idsRegeneration_driver_0006
	IMPORT_FUNC  "idsRegeneration_driver",0x87A30D3A,idsRegenerationGetSerialKey
#endif
#ifdef F_idsRegeneration_driver_0007
	IMPORT_FUNC  "idsRegeneration_driver",0xE37CC2E6,idsRegenerationGetWlanKey
#endif
#ifdef F_idsRegeneration_driver_0008
	IMPORT_FUNC  "idsRegeneration_driver",0xC44FE956,idsRegenerationGetAudioVolumeSetupKey
#endif
#ifdef F_idsRegeneration_driver_0009
	IMPORT_FUNC  "idsRegeneration_driver",0xBC42FEED,idsRegenerationGetUsbKeys
#endif
#ifdef F_idsRegeneration_driver_0010
	IMPORT_FUNC  "idsRegeneration_driver",0x3F014928,idsRegenerationGetUnkKey140
#endif
#ifdef F_idsRegeneration_driver_0011	
	IMPORT_FUNC  "idsRegeneration_driver",0x8F7EE9C0,idsRegenerationGetMGKey40
#endif
#ifdef F_idsRegeneration_driver_0012	
	IMPORT_FUNC  "idsRegeneration_driver",0xB9156F27,idsRegenerationGetUnkKeys3X
#endif
#ifdef F_idsRegeneration_driver_0013
	IMPORT_FUNC  "idsRegeneration_driver",0xB417BCF0,idsRegenerationGetParentalLockKey
#endif
#ifdef F_idsRegeneration_driver_0014
	IMPORT_FUNC  "idsRegeneration_driver",0xFA2368E8,idsRegenerationGenerateFactoryFirmwareKey
#endif
#ifdef F_idsRegeneration_driver_0015
	IMPORT_FUNC  "idsRegeneration_driver",0x0EF8731D,idsRegenerationGetLCDKey
#endif
#ifdef F_idsRegeneration_driver_0016
	IMPORT_FUNC  "idsRegeneration_driver",0x4E95D36F,idsRegenerationGenerateCallibrationKey
#endif
#ifdef F_idsRegeneration_driver_0017
	IMPORT_FUNC  "idsRegeneration_driver",0xD7603D82,idsRegenerationGetUnkKeys5253
#endif
#ifdef F_idsRegeneration_driver_0018
	IMPORT_FUNC  "idsRegeneration_driver",0x6015A7CD,idsRegenerationGetDefaultXMBColorKey
#endif
#ifdef F_idsRegeneration_driver_0019
	IMPORT_FUNC  "idsRegeneration_driver",0xB79A6C46,idsRegenerationCreateCertificatesAndUMDKeys
#endif
