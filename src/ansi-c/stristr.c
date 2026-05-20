#include <stdlib.h>

extern unsigned int strlen(const char * text);
extern int strncasecmp(const char *a, const char *b, unsigned int count);

char* stristr(const char* source, const char* search){
    int len = strlen(search);
    if (len > 0){
        int i = 0;
        while (source[i] != 0){
            if (strncasecmp(&source[i], search, len)==0){
                return (char*)&source[i];
            }
            i++;
        }
    }
    return NULL;
}
