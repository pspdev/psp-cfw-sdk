PSPSDK=$(shell psp-config --pspsdk-path)
PSPDIR=$(shell psp-config --psp-prefix)
TARGET_LIB = libtinyfont.a
OBJS = tinyfont.o font.o

all: $(TARGET_LIB)
CFLAGS = -std=c99 -O2 -G0 -Wall -s
LDFLAGS =
CXXFLAGS = $(CFLAGS) -fexceptions -fno-rtti
PSP_FW_VERSION=660

include $(PSPSDK)/lib/build.mak
