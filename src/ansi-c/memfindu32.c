#include <stdlib.h>

// Searches for 32-bit value on memory
// Starting address must be word aligned
// Returns pointer to value
unsigned int* memfindu32(const unsigned int val, unsigned int* start, unsigned int size)
{
    unsigned int i = 0;
    while (i < size && *start != val)
    {
        start++;
        i++;
    }

    if (i < size)
        return start;
    else
        return NULL;
}
