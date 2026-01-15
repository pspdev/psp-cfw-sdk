TARGET_LIB=libcolordebugger.a
PSPSDK=$(shell psp-config --pspsdk-path)
PSPDIR=$(shell psp-config --psp-prefix)

C_OBJS = \
colordebugger.o

all: $(TARGET_LIB)

OBJS = $(C_OBJS)
PSPSDK=$(shell psp-config --pspsdk-path)

CC=psp-gcc
INCDIR = ../../include
CFLAGS = -std=c99 -Wall -Os -G0 -fno-pic -lstdc++
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LIBDIR =

include $(PSPSDK)/lib/build.mak
