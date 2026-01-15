
TARGET=libpsppsar.a

all: $(TARGET)
STUBSRC = libpspPSAR.S
OBJS = \
	libpspPSAR_0000.o \
	libpspPSAR_0001.o \
	libpspPSAR_0002.o \
	libpspPSAR_0003.o \
	libpspPSAR_0004.o \

PSPSDK=$(shell psp-config --pspsdk-path)

CC=psp-gcc
INCDIR = 
CFLAGS = -std=c99 -Os -G0 -Wall -fno-builtin-printf -I$(PSPSDK)/include
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LDFLAGS=-nodefaultlibs

LIBDIR =

include ../../build-tools/beauty_stub.mak
