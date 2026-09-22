TARGET_LIB=libpspdownloader.a

C_OBJS = libpspdownloader.o

OBJS = $(C_OBJS)

all: $(TARGET_LIB)

PSPSDK=$(shell psp-config --pspsdk-path)

CC=psp-gcc
INCDIR = ../../include
CFLAGS = -std=c99 -Wall -Os -G0 -fno-pic
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LIBDIR =

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
