.PHONY: all install clean

PSPSDK = $(shell psp-config --pspsdk-path)
PSPDEV = $(shell psp-config --pspdev-path)
CFWSDK = $(PSPDEV)/share/psp-cfw-sdk

all:
	$(MAKE) -C src/KUBridge
	$(MAKE) -C src/SystemCtrlForUser
	$(MAKE) -C src/SystemCtrlForKernel
	$(MAKE) -C src/VshCtrl
	$(MAKE) -C src/ArkCtrl
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
	$(MAKE) -C src/ScePafLibc
	$(MAKE) -C src/pspminicrt
	$(MAKE) -C src/ansi-c
	$(MAKE) -C src/pspmalloc
	$(MAKE) -C src/colordebugger
	$(MAKE) -C src/tinyfont
	$(MAKE) -C src/mini2d
	$(MAKE) -C src/libunarchive_helper
	$(MAKE) -C src/LibPspExploit
	$(MAKE) -C src/BootLoadEx
	$(MAKE) -C src/LibCisoRead
	$(MAKE) -C src/popsdisplay
	$(MAKE) -C src/iplsdk
	$(MAKE) -C src/microlz
	$(MAKE) -C src/idstorage_ms
	mkdir -p libs
	mkdir -p include/iplsdk
	cp src/pre-built/*.a libs/
	cp src/KUBridge/*.a libs/
	cp src/SystemCtrlForUser/*.a libs
	cp src/SystemCtrlForKernel/*.a libs
	cp src/VshCtrl/*.a libs
	cp src/ArkCtrl/*.a libs
	cp src/AdrenalineCtrl/*.a libs
	cp src/SysclibForUser/*.a libs
	cp src/inferno_driver/*.a libs
	cp src/isoCtrl_driver/*.a libs
	cp src/DcManager/*.a libs
	cp src/idsRegeneration/*.a libs
	cp src/idsRegeneration_driver/*.a libs
	cp src/pspIplUpdate/*.a libs
	cp src/pspKbootiUpdate/*.a libs
	cp src/pspDecrypt/*.a libs
	cp src/pspPSAR/*.a libs
	cp src/kpspident/*.a libs
	cp src/libintraFont_stub/*.a libs
	cp src/libpspav_stub/*.a libs
	cp src/libpspftp_stub/*.a libs
	cp src/libpng_stub/*.a libs
	cp src/guglue/*.a libs
	cp src/ScePafLibc/*.a libs
	cp src/pspminicrt/*.a libs
	cp src/ansi-c/*.a libs
	cp src/pspmalloc/*.a libs
	cp src/colordebugger/*.a libs
	cp src/tinyfont/*.a libs
	cp src/tinyfont/tinyfont.h include
	cp src/mini2d/*.a libs
	cp src/libunarchive_helper/*.a libs
	cp src/LibPspExploit/*.a libs
	cp src/LibPspExploit/*.h include
	cp src/BootLoadEx/*.a libs
	cp src/LibCisoRead/*.a libs
	cp src/popsdisplay/*.h include
	cp src/popsdisplay/*.a libs
	cp src/iplsdk/*.a libs
	cp src/iplsdk/include/*.h include/iplsdk
	cp src/microlz/*.a libs
	cp src/idstorage_ms/*.a libs

install: all
	cp -r include/* $(PSPSDK)/include/
	cp -r libs/* $(PSPSDK)/lib/
	mkdir -p $(CFWSDK)/build-tools
	cp -r build-tools $(CFWSDK)/

clean:
	rm -rf libs
	rm -rf include/iplsdk
	rm -f  include/libpspexploit.h
	rm -f  include/tinyfont.h
	rm -f  include/popsdisplay.h
	$(MAKE) -C src/KUBridge clean
	$(MAKE) -C src/SystemCtrlForUser clean
	$(MAKE) -C src/SystemCtrlForKernel clean
	$(MAKE) -C src/VshCtrl clean
	$(MAKE) -C src/ArkCtrl clean
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
	$(MAKE) -C src/ScePafLibc clean
	$(MAKE) -C src/pspminicrt clean
	$(MAKE) -C src/ansi-c clean
	$(MAKE) -C src/pspmalloc clean
	$(MAKE) -C src/colordebugger clean
	$(MAKE) -C src/tinyfont clean
	$(MAKE) -C src/mini2d clean
	$(MAKE) -C src/libunarchive_helper clean
	$(MAKE) -C src/LibPspExploit clean
	$(MAKE) -C src/BootLoadEx clean
	$(MAKE) -C src/LibCisoRead clean
	$(MAKE) -C src/popsdisplay clean
	$(MAKE) -C src/iplsdk clean
	$(MAKE) -C src/microlz clean
	$(MAKE) -C src/idstorage_ms clean
