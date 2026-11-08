TARGET=libmectrl.a

all: $(TARGET)
STUBSRC = MEControl.S
OBJS = \
	MECtrl_0000.o \
	MECtrl_0001.o \
	MECtrl_0002.o \
	MECtrl_0003.o \
	MECtrl_0004.o \
	MECtrl_0005.o \
	MECtrl_0006.o \


PSPSDK=$(shell psp-config --pspsdk-path)

CC=psp-gcc
INCDIR =
CFLAGS = -std=c99 -Os -G0 -Wall -fno-builtin-printf -I$(PSPSDK)/include
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LDFLAGS=-nodefaultlibs

LIBDIR =

include ../../build-tools/beauty_stub.mak
