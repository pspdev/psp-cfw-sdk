#include <stdlib.h>

extern int strcmp(const char *a, const char *b);

// Searches for s1 string on memory
// Returns pointer to string
char* memfindsz(const char* s1, char* start, unsigned int size)
{
    unsigned int i = 0;
    while (i < size && strcmp(start, s1) != 0)
    {
        start++;
        i++;
    }

    if (i < size)
        return start;
    else
        return NULL;
}
