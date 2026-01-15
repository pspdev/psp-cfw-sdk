#include <string.h>

#include "bootloadex.h"

int pspemuLfatOpenArkEPSX(BootFile* file)
{
    char* p = file->name;
    if (strcmp(p, "pspbtcnf.bin") == 0){
        p[2] = 'x'; // custom btcnf for VitaPops
    }
    return -1;
}
