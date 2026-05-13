#include <string.h>

char *stpcpy(char *to, const char *from){
    char *oto = to;
    
    // Position
    unsigned int position = 0;
    
    // Copy Bytes
    while(from[position] != 0)
    {
        // Copy Byte
        to[position] = from[position];
        
        // Change Position
        position++;
    }
    
    // Terminate String
    to[position] = 0;
    
    return &to[position];
}
