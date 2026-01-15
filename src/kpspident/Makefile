
TARGET=libkpspident.a

all: $(TARGET)
STUBSRC = libkpspident.S
OBJS = \
	libkpspident_0000.o \
	libkpspident_0001.o \
	libkpspident_0002.o \
	libkpspident_0003.o \
	libkpspident_0004.o \
	libkpspident_0005.o \

PSPSDK=$(shell psp-config --pspsdk-path)

CC=psp-gcc
INCDIR = 
CFLAGS = -std=c99 -Os -G0 -Wall -fno-builtin-printf -I$(PSPSDK)/include
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LDFLAGS=-nodefaultlibs

LIBDIR =

include ../../build-tools/beauty_stub.mak
