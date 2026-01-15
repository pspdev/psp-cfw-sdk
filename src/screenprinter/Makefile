PSPSDK=$(shell psp-config --pspsdk-path)
PSPDIR=$(shell psp-config --psp-prefix)
TARGET_LIB = libscreenprinter.a
OBJS = lib.o font.o screenprinter.o

all: $(TARGET_LIB)
CFLAGS = -std=c99 -O2 -G0 -Wall -s -lstdc++ -I ../../include -L ../colordebugger
LDFLAGS = -lcolordebugger
CXXFLAGS = $(CFLAGS) -fexceptions -fno-rtti
PSP_FW_VERSION=660

include $(PSPSDK)/lib/build.mak
