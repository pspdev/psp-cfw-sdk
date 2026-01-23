TARGET=libarkctrl.a

all: $(TARGET)
STUBSRC = ArkControl.S
OBJS = \
	ArkCtrl_0000.o \
	ArkCtrl_0001.o \
	ArkCtrl_0002.o \


PSPSDK=$(shell psp-config --pspsdk-path)

CC=psp-gcc
INCDIR =
CFLAGS = -std=c99 -Os -G0 -Wall -fno-builtin-printf -I$(PSPSDK)/include
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LDFLAGS=-nodefaultlibs

LIBDIR =

include ../../build-tools/beauty_stub.mak
