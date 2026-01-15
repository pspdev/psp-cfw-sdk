
TARGET=libpspdecrypt.a

all: $(TARGET)
STUBSRC = libpspDecrypt.S
OBJS = \
	libpspDecrypt_0000.o \
	libpspDecrypt_0001.o \
	libpspDecrypt_0002.o \
	libpspDecrypt_0003.o \
	libpspDecrypt_0004.o \
	libpspDecrypt_0005.o \
	libpspDecrypt_0006.o \
	libpspDecrypt_0007.o \

PSPSDK=$(shell psp-config --pspsdk-path)

CC=psp-gcc
INCDIR = 
CFLAGS = -std=c99 -Os -G0 -Wall -fno-builtin-printf -I$(PSPSDK)/include
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LDFLAGS=-nodefaultlibs

LIBDIR =

include ../../build-tools/beauty_stub.mak
