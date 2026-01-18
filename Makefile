.PHONY: all install clean

PSPSDK = $(shell psp-config --pspsdk-path)
PSPDEV = $(shell psp-config --pspdev-path)
CFWSDK = $(PSPDEV)/share/psp-cfw-sdk

all:
	$(MAKE) -C src/KUBridge
	$(MAKE) -C src/SystemCtrlForUser
	$(MAKE) -C src/SystemCtrlForKernel
	$(MAKE) -C src/VshCtrl
	$(MAKE) -C src/AdrenalineCtrl
	$(MAKE) -C src/SysclibForUser
	$(MAKE) -C src/inferno_driver
	$(MAKE) -C src/isoCtrl_driver
	$(MAKE) -C src/DcManager
	$(MAKE) -C src/idsRegeneration
	$(MAKE) -C src/idsRegeneration_driver
	$(MAKE) -C src/pspIplUpdate
	$(MAKE) -C src/pspKbootiUpdate
	$(MAKE) -C src/pspDecrypt
	$(MAKE) -C src/pspPSAR
	$(MAKE) -C src/kpspident
	$(MAKE) -C src/libintraFont_stub
	$(MAKE) -C src/libpspav_stub
	$(MAKE) -C src/libpspftp_stub
	$(MAKE) -C src/libpng_stub
	$(MAKE) -C src/guglue
	$(MAKE) -C src/ansi-c
	$(MAKE) -C src/colordebugger
	$(MAKE) -C src/screenprinter
	$(MAKE) -C src/mini2d
	$(MAKE) -C src/LibPspExploit
	$(MAKE) -C src/BootLoadEx
	$(MAKE) -C src/LibCisoRead
	$(MAKE) -C src/iplsdk
	$(MAKE) -C src/microlz
	$(Q)mkdir -p libs
	$(Q)mkdir -p include/iplsdk
	$(Q)cp src/pre-built/*.a libs/
	$(Q)cp src/KUBridge/*.a libs/
	$(Q)cp src/SystemCtrlForUser/*.a libs
	$(Q)cp src/SystemCtrlForKernel/*.a libs
	$(Q)cp src/VshCtrl/*.a libs
	$(Q)cp src/AdrenalineCtrl/*.a libs
	$(Q)cp src/SysclibForUser/*.a libs
	$(Q)cp src/inferno_driver/*.a libs
	$(Q)cp src/isoCtrl_driver/*.a libs
	$(Q)cp src/DcManager/*.a libs
	$(Q)cp src/idsRegeneration/*.a libs
	$(Q)cp src/idsRegeneration_driver/*.a libs
	$(Q)cp src/pspIplUpdate/*.a libs
	$(Q)cp src/pspKbootiUpdate/*.a libs
	$(Q)cp src/pspDecrypt/*.a libs
	$(Q)cp src/pspPSAR/*.a libs
	$(Q)cp src/kpspident/*.a libs
	$(Q)cp src/libintraFont_stub/*.a libs
	$(Q)cp src/libpspav_stub/*.a libs
	$(Q)cp src/libpspftp_stub/*.a libs
	$(Q)cp src/libpng_stub/*.a libs
	$(Q)cp src/guglue/*.a libs
	$(Q)cp src/ansi-c/*.a libs
	$(Q)cp src/colordebugger/*.a libs
	$(Q)cp src/screenprinter/*.a libs
	$(Q)cp src/mini2d/*.a libs
	$(Q)cp src/LibPspExploit/*.a libs
	$(Q)cp src/LibPspExploit/*.h include/
	$(Q)cp src/BootLoadEx/*.a libs
	$(Q)cp src/BootLoadEx/bootloadex*.h include/
	$(Q)cp src/LibCisoRead/*.a libs
	$(Q)cp src/LibCisoRead/ciso*.h include/
	$(Q)cp src/iplsdk/*.a libs
	$(Q)cp src/iplsdk/include/*.h include/iplsdk
	$(Q)cp src/microlz/*.a libs

install: all
	$(Q)cp -r include/* $(PSPSDK)/include/
	$(Q)cp -r libs/* $(PSPSDK)/lib/
	$(Q)mkdir -p $(CFWSDK)/build-tools
	$(Q)cp -r build-tools $(CFWSDK)/

clean:
	$(Q)rm -rf libs
	$(Q)rm -rf include/iplsdk
	$(Q)rm -f include/bootloadex*.h
	$(Q)rm -f include/ciso*.h
	$(MAKE) -C src/KUBridge clean
	$(MAKE) -C src/SystemCtrlForUser clean
	$(MAKE) -C src/SystemCtrlForKernel clean
	$(MAKE) -C src/VshCtrl clean
	$(MAKE) -C src/AdrenalineCtrl clean
	$(MAKE) -C src/SysclibForUser clean
	$(MAKE) -C src/inferno_driver clean
	$(MAKE) -C src/isoCtrl_driver clean
	$(MAKE) -C src/DcManager clean
	$(MAKE) -C src/idsRegeneration clean
	$(MAKE) -C src/idsRegeneration_driver clean
	$(MAKE) -C src/pspIplUpdate clean
	$(MAKE) -C src/pspKbootiUpdate clean
	$(MAKE) -C src/pspDecrypt clean
	$(MAKE) -C src/pspPSAR clean
	$(MAKE) -C src/kpspident clean
	$(MAKE) -C src/libintraFont_stub clean
	$(MAKE) -C src/libpspav_stub clean
	$(MAKE) -C src/libpspftp_stub clean
	$(MAKE) -C src/libpng_stub clean
	$(MAKE) -C src/guglue clean
	$(MAKE) -C src/ansi-c clean
	$(MAKE) -C src/colordebugger clean
	$(MAKE) -C src/screenprinter clean
	$(MAKE) -C src/mini2d clean
	$(MAKE) -C src/LibPspExploit clean
	$(MAKE) -C src/BootLoadEx clean
	$(MAKE) -C src/LibCisoRead clean
	$(MAKE) -C src/iplsdk clean
	$(MAKE) -C src/microlz clean
