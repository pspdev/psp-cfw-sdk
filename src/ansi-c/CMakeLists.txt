add_sdk_library(ansic)

target_sources(ansic PRIVATE
   memmove.c
   memcmp.c
   memcpy.c
   memset.c
   strcpy.c
   strcat.c
   strlen.c
   strnlen.c
   strchr.c
   strrchr.c
   strcmp.c
   strncmp.c
   strstr.c
   stristr.c
   strspn.c
   strcspn.c
   strtok.c
   memfindsz.c
   memfindu32.c
   strhex32.c
   strncpy.c
   strncat.c
   strncat_s.c
   strncpy_s.c
   strbeginswith.c
   strreplaceall.c
   strcasecmp.c
   tolower.c
   lowerstring.c
   setlongjmp.S
)

target_compile_options(ansic PRIVATE -fno-builtin)