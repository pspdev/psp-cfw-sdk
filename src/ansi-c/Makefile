TARGET_LIB=libansic.a

C_OBJS = \
	arith64.o \
	atof.o \
    isalnum.o \
    isalpha.o \
	isascii.o \
    isblank.o \
    iscntrl.o \
    isdigit.o \
    isgraph.o \
    islower.o \
    isprint.o \
    ispunct.o \
    isspace.o \
    isupper.o \
    isxdigit.o \
	lowerstring.o \
	memcmp.o \
	memcpy.o \
	memfindsz.o \
	memfindu32.o \
	memmove.o \
	memset.o \
	printf.o \
	rand.o \
	setlongjmp.o \
	strcpy.o \
	strbeginswith.o \
	strcasecmp.o \
	strcat.o \
	strchr.o \
	strcmp.o \
	stpcpy.o \
	strcspn.o \
	strdup.o \
	strhex32.o \
	strhex64.o \
	stristr.o \
	strlen.o \
	strncat_s.o \
	strncat.o \
	strncmp.o \
	strncpy_s.o \
	strncpy.o \
	strndup.o \
	strnlen.o \
	strrchr.o \
	strreplaceall.o \
	strspn.o \
	strstr.o \
	strtok.o \
	strtol.o \
	strtoul.o \
	strtrim.o \
	toascii.o \
	tolower.o \
	toupper.o

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
