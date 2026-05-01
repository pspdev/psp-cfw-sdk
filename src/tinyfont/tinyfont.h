
#ifndef TINYFONT_H
#define TINYFONT_H

#include <pspsdk.h>

typedef struct TinyFontState{
    int scroll; // enable/disable text scroll
    int sk; // scroll skip time (in frames)
    int sx; // current scroll x position
    int ci; // current scroll text index
    int ix; // initial scroll index
    int glow; // enable/disable text glow
    u8 sc; // current shadow color for glow
    u8 sd; // current shadow direction (increase/decrease), for glow
} TinyFontState;

void tinyFontPrintText(u32* frame, u8* font, int x, int y, const char* text, u32 color, TinyFontState* state);

#endif
