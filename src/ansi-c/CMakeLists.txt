add_library(ansic STATIC)

target_sources(ansic PRIVATE
   memmove.c
   memcmp.c
   memcpy.c
   memset.c
   strcpy.c
   strlen.c
   strchr.c
   strcmp.c
   strstr.c
   memfind.c
   strhex32.c
   strsafe.c
   strbeginswith.c
   strreplaceall.c
   strcasecmp.c
   lowerstring.c
)

target_compile_options(ansic PRIVATE -std=c99 -Wall -Os -G0 -fno-pic)

add_dependencies(ansic CopyPrebuiltSdkLibs)

add_custom_command(TARGET ansic POST_BUILD
   COMMAND cp "$<TARGET_FILE:ansic>" "${SDK_LIBS_DIR}/"
   COMMENT "Copying to libs folder"
)
