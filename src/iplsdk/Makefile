TARGET_LIB = libiplsdk.a
OBJS = \
	src/cache.o \
	src/cpu.o \
	src/display.o \
	src/dmacplus.o \
	src/emcddr.o \
	src/chip.o \
	src/ecc.o \
	src/emcsm.o \
	src/scramble.o \
	src/state.o \
	src/exception.o \
	src/exception_asm.o \
	src/gpio.o \
	src/interrupt.o \
	src/interrupt_asm.o \
	src/kirk.o \
	src/lcd.o \
	src/phatlcd.o \
	src/hibari.o \
	src/samantha.o \
	src/streetlcd.o \
	src/tmdlcd.o \
	src/lcdc.o \
	src/led.o \
	src/lflash.o \
	src/model.o \
	src/mspro.o \
	src/ms.o \
	src/pwm.o \
	src/spi.o \
	src/comms.o \
	src/handshake.o \
	src/syscon.o \
	src/sysreg.o \
	src/uart.o \
	src/delay.o \
	src/fat.o \
	src/utils.o


INCDIR = include
CFLAGS = -Os -G0 -Wall -fno-pic -std=c99 $(BFLAGS) -fdata-sections -ffunction-sections -Wl,--gc-sections
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti 
ASFLAGS = $(CFLAGS)

LIBS =
LIBDIR = 
LDFLAGS = 


PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
