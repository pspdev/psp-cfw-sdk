TARGET=libpspinferno_driver.a

all: $(TARGET)
STUBSRC = inferno_driver.S
OBJS = \
	inferno_driver_0000.o \
	inferno_driver_0001.o \
	inferno_driver_0002.o \
	inferno_driver_0003.o \
	inferno_driver_0004.o \
	inferno_driver_0005.o \

PSPSDK=$(shell psp-config --pspsdk-path)

CC=psp-gcc
INCDIR = 
CFLAGS = -std=c99 -Os -G0 -Wall -fno-builtin-printf -I$(PSPSDK)/include
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LDFLAGS=-nodefaultlibs

LIBDIR =

include ../../build-tools/beauty_stub.mak
