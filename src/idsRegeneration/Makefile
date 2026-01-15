TARGET=libidsregeneration.a

all: $(TARGET)
STUBSRC = idsRegeneration.S
OBJS = \
	idsRegeneration_0000.o \
	idsRegeneration_0001.o \
	idsRegeneration_0002.o \
	idsRegeneration_0003.o \
	idsRegeneration_0004.o \
	idsRegeneration_0005.o \
	idsRegeneration_0006.o \
	idsRegeneration_0007.o \
	idsRegeneration_0008.o \
	idsRegeneration_0009.o \
	idsRegeneration_0010.o \
	idsRegeneration_0011.o \
	idsRegeneration_0012.o \
	idsRegeneration_0013.o \
	idsRegeneration_0014.o \
	idsRegeneration_0015.o \
	idsRegeneration_0016.o \
	idsRegeneration_0017.o \
	idsRegeneration_0018.o \
	idsRegeneration_0019.o \

PSPSDK=$(shell psp-config --pspsdk-path)

CC=psp-gcc
INCDIR = 
CFLAGS = -std=c99 -Os -G0 -Wall -fno-builtin-printf -I$(PSPSDK)/include
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LDFLAGS=-nodefaultlibs

LIBDIR =

include ../../build-tools/beauty_stub.mak
