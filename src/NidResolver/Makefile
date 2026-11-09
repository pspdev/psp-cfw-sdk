TARGET=libnidresolver.a

all: $(TARGET)
STUBSRC = NidResolverForKernel.S
OBJS = \
	NidResolverForKernel_0000.o \
	NidResolverForKernel_0001.o \
	NidResolverForKernel_0002.o \
	NidResolverForKernel_0003.o \


PSPSDK=$(shell psp-config --pspsdk-path)

CC=psp-gcc
INCDIR =
CFLAGS = -std=c99 -Os -G0 -Wall -fno-builtin-printf -I$(PSPSDK)/include
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LDFLAGS=-nodefaultlibs

LIBDIR =

include ../../build-tools/beauty_stub.mak
