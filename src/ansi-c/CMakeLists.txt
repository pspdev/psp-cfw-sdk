add_sdk_library(ansic)

target_sources(ansic PRIVATE
   atof.c
   lowerstring.c
   memcmp.c
   memcpy.c
   memfindsz.c
   memfindu32.c
   memmove.c
   memset.c
   printf.c
   rand.c
   setlongjmp.S
   strbeginswith.c
   strcasecmp.c
   strcat.c
   strchr.c
   strcmp.c
   strcpy.c
   strcspn.c
   strdup.c
   strhex32.c
   strhex64.c
   stristr.c
   strlen.c
   strncat.c
   strncat_s.c
   strncmp.c
   strncpy.c
   strncpy_s.c
   strnlen.c
   strrchr.c
   strreplaceall.c
   strspn.c
   strstr.c
   strtok.c
   tolower.c
)

target_compile_options(ansic PRIVATE -fno-builtin)