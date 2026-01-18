TARGET=libpspisoctrl_driver.a

all: $(TARGET)
STUBSRC = isoCtrl_driver.S
OBJS = \
	isoCtrl_driver_0000.o \
	isoCtrl_driver_0001.o \
	isoCtrl_driver_0002.o \
	isoCtrl_driver_0003.o

PSPSDK=$(shell psp-config --pspsdk-path)

CC=psp-gcc
INCDIR =
CFLAGS = -std=c99 -Os -G0 -Wall -fno-builtin-printf -I$(PSPSDK)/include
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LDFLAGS=-nodefaultlibs

LIBDIR =

include ../../build-tools/beauty_stub.mak