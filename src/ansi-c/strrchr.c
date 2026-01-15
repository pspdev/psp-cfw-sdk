#include <stdlib.h>

char * strrchr(const char *cp, int ch)
{
    char *save;
    char c;

    for (save = (char *) NULL; (c = *cp); cp++) {
        if (c == ch)
            save = (char *) cp;
    }

    return save;
}
