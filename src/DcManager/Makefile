TARGET=libpspdcman.a

all: $(TARGET)
STUBSRC = DcManager.S
OBJS = \
	DcManager_0000.o \
	DcManager_0001.o \
	DcManager_0002.o \
	DcManager_0003.o \
	DcManager_0004.o \
	DcManager_0005.o \
	DcManager_0006.o \
	DcManager_0007.o \
	DcManager_0008.o \
	DcManager_0009.o \
	DcManager_0010.o \
	DcManager_0011.o \
	DcManager_0012.o \
	DcManager_0013.o \
	DcManager_0014.o \
	DcManager_0015.o \
	DcManager_0016.o \
	DcManager_0017.o \
	DcManager_0018.o \
	DcManager_0019.o \
	DcManager_0020.o \
	DcManager_0021.o \
	DcManager_0022.o \
	DcManager_0023.o \
	DcManager_0024.o \
	DcManager_0025.o \
	DcManager_0026.o \
	DcManager_0027.o \

PSPSDK=$(shell psp-config --pspsdk-path)

CC=psp-gcc
INCDIR = 
CFLAGS = -std=c99 -Os -G0 -Wall -fno-builtin-printf -I$(PSPSDK)/include
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LDFLAGS=-nodefaultlibs

LIBDIR =

include ../../build-tools/beauty_stub.mak
