TARGET=libpsppaf.a

all: $(TARGET)
STUBSRC = ScePaf.S
OBJS = \
	ScePaf_0000.o \
	ScePaf_0001.o \
	ScePaf_0002.o \
	ScePaf_0003.o \
	ScePaf_0004.o \
	ScePaf_0005.o \
	ScePaf_0006.o \
	ScePaf_0007.o \
	ScePaf_0008.o \
	ScePaf_0009.o \
	ScePaf_0010.o \
	ScePaf_0011.o \
	ScePaf_0012.o \
	ScePaf_0013.o \
	ScePaf_0014.o \
	ScePaf_0015.o \
	ScePaf_0016.o \
	ScePaf_0017.o \

PSPSDK=$(shell psp-config --pspsdk-path)

CC=psp-gcc
INCDIR =
CFLAGS = -std=c99 -Os -G0 -Wall -fno-builtin-printf -I$(PSPSDK)/include
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LDFLAGS=-nodefaultlibs

LIBDIR =

include ../../build-tools/beauty_stub.mak
