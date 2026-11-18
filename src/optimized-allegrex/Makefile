TARGET_LIB = liboptimized-allegrex.a

OBJS = \
    src/__ashldi3.o \
    src/__ashrdi3.o \
    src/__bitops.o \
    src/__bswap.o \
    src/__cmpdi2.o \
    src/__divmoddi4.o \
    src/__lshrdi3.o \
    src/__muldi3.o

ifeq ($(BUILD_ALL),1)
OBJS += src/__udivmoddi4.o
endif

PSPSDK = $(shell psp-config --pspsdk-path)

CC = psp-gcc
CFLAGS = -Os -G0 -Wall -fno-pic
ASFLAGS = $(CFLAGS)
LIBDIR =

all: $(TARGET_LIB)

include $(PSPSDK)/lib/build.mak