#include <stdlib.h>

extern unsigned int strlen(const char * text);
extern int strncmp(const char *a, const char *b, unsigned int count);

char* strstr(const char* source, const char* search){
    int len = strlen(search)-1;
    if (len > 0){
        int i = 0;
        while (source[i] != 0){
            if (strncmp(&source[i], search, len)==0){
                return (char*)&source[i];
            }
            i++;
        }
    }
    return NULL;
}
