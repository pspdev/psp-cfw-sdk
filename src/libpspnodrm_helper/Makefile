TARGET=libpspnodrm_helper.a

all: $(TARGET)
STUBSRC = libpspnodrm_helper.S
OBJS = \
	libpspnodrm_helper_0000.o \
	libpspnodrm_helper_0001.o \
	libpspnodrm_helper_0002.o \
	libpspnodrm_helper_0003.o \

PSPSDK=$(shell psp-config --pspsdk-path)

CC=psp-gcc
INCDIR = 
CFLAGS = -std=c99 -Os -G0 -Wall -fno-builtin-printf -I$(PSPSDK)/include
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LDFLAGS=-nodefaultlibs

LIBDIR =

include ../../build-tools/beauty_stub.mak
