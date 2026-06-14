TARGET=libpspcpaf.a

all: $(TARGET)
STUBSRC = ScePafLibc.S
OBJS = \
	ScePafLibc_0000.o \
	ScePafLibc_0001.o \
	ScePafLibc_0002.o \
	ScePafLibc_0003.o \
	ScePafLibc_0004.o \
	ScePafLibc_0005.o \
	ScePafLibc_0006.o \
	ScePafLibc_0007.o \
	ScePafLibc_0008.o \
	ScePafLibc_0009.o \
	ScePafLibc_0010.o \
	ScePafLibc_0011.o \
	ScePafLibc_0012.o \
	ScePafLibc_0013.o \
	ScePafLibc_0014.o \
	ScePafLibc_0015.o \
	ScePafLibc_0016.o \
	ScePafLibc_0017.o \
	ScePafLibc_0018.o \
	ScePafLibc_0019.o \
	ScePafLibc_0020.o \
	ScePafLibc_0021.o \
	ScePafLibc_0022.o \
	ScePafLibc_0023.o \
	ScePafLibc_0024.o \
	ScePafLibc_0025.o \
	ScePafLibc_0026.o \
	ScePafLibc_0027.o \
	ScePafLibc_0028.o \
	ScePafLibc_0029.o \
	ScePafLibc_0030.o \
	ScePafLibc_0031.o \
	ScePafLibc_0032.o \
	ScePafLibc_0033.o \
	ScePafLibc_0034.o \
	ScePafLibc_0035.o \
	ScePafLibc_0036.o \
	ScePafLibc_0037.o \
	ScePafLibc_0038.o \
	ScePafLibc_0039.o \
	ScePafLibc_0040.o \
	ScePafLibc_0041.o \
	ScePafLibc_0042.o \
	ScePafLibc_0043.o \
	ScePafLibc_0044.o \
	ScePafLibc_0045.o \
	ScePafLibc_0046.o \
	ScePafLibc_0047.o \
	ScePafLibc_0048.o \
	ScePafLibc_0049.o \
	ScePafLibc_0050.o \
	ScePafLibc_0051.o \
	ScePafLibc_0052.o \
	ScePafLibc_0053.o \
	ScePafLibc_0054.o \
	ScePafLibc_0055.o \
	ScePafLibc_0056.o \
	ScePafLibc_0057.o \
	ScePafLibc_0058.o \
	ScePafLibc_0059.o \
	ScePafLibc_0060.o \
	ScePafLibc_0061.o \
	ScePafLibc_0062.o \
	ScePafLibc_0063.o \
	ScePafLibc_0064.o \
	ScePafLibc_0065.o \
	ScePafLibc_0066.o \
	ScePafLibc_0067.o \
	ScePafLibc_0068.o \
	ScePafLibc_0069.o \
	ScePafLibc_0070.o \
	ScePafLibc_0071.o \
	ScePafLibc_0072.o \
	ScePafLibc_0073.o \
	ScePafLibc_0074.o \
	ScePafLibc_0075.o \
	ScePafLibc_0076.o


PSPSDK=$(shell psp-config --pspsdk-path)

CC=psp-gcc
INCDIR =
CFLAGS = -std=c99 -Os -G0 -Wall -I$(PSPSDK)/include
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LDFLAGS=-nodefaultlibs

LIBDIR =

include ../../build-tools/beauty_stub.mak
