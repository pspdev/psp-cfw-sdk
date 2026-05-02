
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

extern u8 msx[]; // built-in font

/**
 * Swap hardcoded draw/display buffers. Use this if you are not specifying a framebuffer (i.e. tinyFontPrintTextScreen).
 */
void tinyFontSwapBuffers();


/**
 * Print a string onto a draw buffer
 * 
 * @param buffer image buffer or framebuffer
 * @param buf_w buffer width
 * @param buf_h buffer height
 * @param pow2_w next power of 2 after buffer width
 * @param font bitmap font, can use built-in msx font
 * @param x coordinate relative to frame buffer
 * @param y coordinate relative to frame buffer
 * @param text string to print onto buffer
 * @param color 32 bit ARGB format color
 * @param state optional, used for effects (glow, scroll, etc) 
 * 
 */
void tinyFontPrintTextBuffer(u32* buffer, int buf_w, int buf_h, int pow2_w, u8* font, int x, int y, const char* text, u32 color, TinyFontState* state);

void tinyFontPrintTextImage(void* image, int img_w, int img_h, u8* font, int x, int y, const char* text, u32 color, TinyFontState* state);

void tinyFontPrintTextScreen(u8* font, int x, int y, const char* text, u32 color, TinyFontState* state);

void tinyFontPrintTextScreenBuf(void* framebuf, u8* font, int x, int y, const char* text, u32 color, TinyFontState* state);


#endif
