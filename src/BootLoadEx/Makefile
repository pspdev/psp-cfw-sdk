TARGET_LIB=libbootloadex.a

C_OBJS = \
	crt0.o \
	bootloadex.o \
	scanner.o \
	pspbtcnf.o \
	patches_psp.o \
	patches_vita.o \
	bootloadex_ark.o \
	patches_psp_ark.o \


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
