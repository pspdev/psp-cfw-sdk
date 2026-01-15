TARGET=libidsregeneration_driver.a

all: $(TARGET)
STUBSRC = idsRegeneration_driver.S
OBJS = \
	idsRegeneration_driver_0000.o \
	idsRegeneration_driver_0001.o \
	idsRegeneration_driver_0002.o \
	idsRegeneration_driver_0003.o \
	idsRegeneration_driver_0004.o \
	idsRegeneration_driver_0005.o \
	idsRegeneration_driver_0006.o \
	idsRegeneration_driver_0007.o \
	idsRegeneration_driver_0008.o \
	idsRegeneration_driver_0009.o \
	idsRegeneration_driver_0010.o \
	idsRegeneration_driver_0011.o \
	idsRegeneration_driver_0012.o \
	idsRegeneration_driver_0013.o \
	idsRegeneration_driver_0014.o \
	idsRegeneration_driver_0015.o \
	idsRegeneration_driver_0016.o \
	idsRegeneration_driver_0017.o \
	idsRegeneration_driver_0018.o \
	idsRegeneration_driver_0019.o \

PSPSDK=$(shell psp-config --pspsdk-path)

CC=psp-gcc
INCDIR = 
CFLAGS = -std=c99 -Os -G0 -Wall -fno-builtin-printf -I$(PSPSDK)/include
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LDFLAGS=-nodefaultlibs

LIBDIR =

include ../../build-tools/beauty_stub.mak
