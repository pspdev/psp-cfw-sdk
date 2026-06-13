TARGET=libpspcpaf.a

all: $(TARGET)
STUBSRC = ScePaf.S
OBJS = \
	ScePaf_0000.o \
	ScePaf_0001.o \
	ScePaf_0002.o \
	ScePaf_0003.o \
	ScePaf_0004.o \
	ScePaf_0005.o \
	ScePaf_0006.o \
	ScePaf_0007.o \
	ScePaf_0008.o \
	ScePaf_0009.o \
	ScePaf_0010.o \
	ScePaf_0011.o \
	ScePaf_0012.o \
	ScePaf_0013.o \
	ScePaf_0014.o \
	ScePaf_0015.o \
	ScePaf_0016.o \
	ScePaf_0017.o \
	ScePaf_0018.o \
	ScePaf_0019.o \
	ScePaf_0020.o \
	ScePaf_0021.o \
	ScePaf_0022.o \
	ScePaf_0023.o \
	ScePaf_0024.o \
	ScePaf_0025.o \
	ScePaf_0026.o \
	ScePaf_0027.o \
	ScePaf_0028.o \
	ScePaf_0029.o \
	ScePaf_0030.o \
	ScePaf_0031.o \
	ScePaf_0032.o \
	ScePaf_0033.o \
	ScePaf_0034.o \
	ScePaf_0035.o \
	ScePaf_0036.o \
	ScePaf_0037.o \
	ScePaf_0038.o \
	ScePaf_0039.o \
	ScePaf_0040.o \
	ScePaf_0041.o \
	ScePaf_0042.o \
	ScePaf_0043.o \
	ScePaf_0044.o \
	ScePaf_0045.o \
	ScePaf_0046.o \
	ScePaf_0047.o \
	ScePaf_0048.o \
	ScePaf_0049.o \
	ScePaf_0050.o \
	ScePaf_0051.o \
	ScePaf_0052.o \
	ScePaf_0053.o \
	ScePaf_0054.o \
	ScePaf_0055.o \
	ScePaf_0056.o \
	ScePaf_0057.o \
	ScePaf_0058.o \
	ScePaf_0059.o \
	ScePaf_0060.o \
	ScePaf_0061.o \
	ScePaf_0062.o \
	ScePaf_0063.o \
	ScePaf_0064.o \
	ScePaf_0065.o \
	ScePaf_0066.o \
	ScePaf_0067.o \
	ScePaf_0068.o \
	ScePaf_0069.o \
	ScePaf_0070.o \
	ScePaf_0071.o \
	ScePaf_0072.o \
	ScePaf_0073.o \
	ScePaf_0074.o \
	ScePaf_0075.o \
	ScePaf_0076.o


PSPSDK=$(shell psp-config --pspsdk-path)

CC=psp-gcc
INCDIR =
CFLAGS = -std=c99 -Os -G0 -Wall -fno-builtin-printf -I$(PSPSDK)/include
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LDFLAGS=-nodefaultlibs

LIBDIR =

include ../../build-tools/beauty_stub.mak
