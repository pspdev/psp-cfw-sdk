TARGET_LIB=libansic.a

C_OBJS = \
	memmove.o \
	memcmp.o \
	memcpy.o \
	memset.o \
	strcpy.o \
	strcat.o \
	strlen.o \
	strnlen.o \
	strchr.o \
	strrchr.o \
	strcmp.o \
	strncmp.o \
	strstr.o \
	stristr.o \
	strspn.o \
	strcspn.o \
	strtok.o \
	memfindsz.o \
	memfindu32.o \
	strhex32.o \
	strncpy.o \
	strncat.o \
	strncat_s.o \
	strncpy_s.o \
	strbeginswith.o \
	strreplaceall.o \
	strcasecmp.o \
	tolower.o \
	lowerstring.o \
	setlongjmp.o

OBJS = $(C_OBJS)

all: $(TARGET_LIB)

PSPSDK=$(shell psp-config --pspsdk-path)

CC=psp-gcc
INCDIR = 
CFLAGS = -std=c99 -Wall -Os -G0 -fno-pic -fno-builtin
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LIBDIR =

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
