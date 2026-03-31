#include <stddef.h>

extern void* malloc(size_t);
extern int strlen(const char*);
extern char* strcpy(char*, const char*);

char * strdup( const char *str1 ){
    int len = strlen(str1);
    char* str2 = (char*)malloc(len+1);
    if (str2) strcpy(str2, str1);
    return str2;
}
