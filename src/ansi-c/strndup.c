#include <stddef.h>

extern void* malloc(size_t);
extern char* strncpy(char*, const char*, size_t);

char *strndup( const char *str1, size_t size ){
    char* str2 = (char*)malloc(size+1);
    if (str2) strncpy(str2, str1, size);
    return str2;
}
