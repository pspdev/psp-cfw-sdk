TARGET=libadrenalinectrl.a

all: $(TARGET)
STUBSRC = AdrenalineControl.S
OBJS = \
	AdrenalineCtrl_0000.o \
	AdrenalineCtrl_0001.o \
	AdrenalineCtrl_0002.o \
	AdrenalineCtrl_0003.o \
	AdrenalineCtrl_0004.o \


PSPSDK=$(shell psp-config --pspsdk-path)

CC=psp-gcc
INCDIR =
CFLAGS = -std=c99 -Os -G0 -Wall -fno-builtin-printf -I$(PSPSDK)/include
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LDFLAGS=-nodefaultlibs

LIBDIR =

include ../../build-tools/beauty_stub.mak
