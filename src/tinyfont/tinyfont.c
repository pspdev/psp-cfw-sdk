
#include <string.h>
 #include <pspdisplay.h>

#include <tinyfont.h>

#define PSP_LINE_SIZE 512
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

void tinyFontPrintText(u32* frame, u8* font, int x, int y, const char* text, u32 color, TinyFontState* state){
    int c, i, j, l;
    u8 *font_ptr;
    u32 *vram_ptr;
    u32 *vram;

    if (state){
        if (state->scroll){
            if (state->sk) state->sk--;
            else {
                state->sx--;
                if (state->sx < state->ix) {
                    state->ci++;
                    state->sx = state->ix + 8;
                    if (state->ci >= strlen(text)+15){
                        state->ci = 0;
                        state->sk = 120;
                        state->sx = state->ix;
                    }
                }
                if (state->ci < strlen(text)) text += state->ci;
                else return; // nothing to draw...
            }
        }
        if (state->glow){
            if (state->sc >= 250) state->sd = 0;
            else if (state->sc <= 5) state->sd = 1;

            if (state->sd) state->sc += 5;
            else state->sc -= 5;
        }
    }

    for (c = 0; c < strlen(text); c++) {
        if (x < 0 || x + 8 > SCREEN_WIDTH || y < 0 || y + 8 > SCREEN_HEIGHT) break;
        char ch = text[c];
        vram = frame + x + y * PSP_LINE_SIZE;
        
        font_ptr = &font[ (int)ch * 8];
        for (i = l = 0; i < 8; i++, l += 8, font_ptr++) {
            vram_ptr  = vram;
            for (j = 0; j < 8; j++) {
                if ((*font_ptr & (128 >> j))){
                    *vram_ptr = color;
                    // shadow color
                    u32 bgcolor = 0xFF000000;
                    if (state && state->glow){
                        bgcolor = 0xFF000000 | (state->sc<<16) | (state->sc<<8) | (state->sc);
                    }
                    // horizontal shadow
                    if (vram_ptr[-1] != color) vram_ptr[-1] = bgcolor;
                    vram_ptr[1] = bgcolor;
                    // vertical shadow
                    u32* prev_pixel = (u32*)((u32)vram_ptr - (4*PSP_LINE_SIZE));
                    u32* post_pixel = (u32*)((u32)vram_ptr + (4*PSP_LINE_SIZE));
                    if (*prev_pixel != color) *prev_pixel = bgcolor;
                    *post_pixel = bgcolor;
                }
                vram_ptr++;
            }
            vram += PSP_LINE_SIZE;
        }
        x += 8;
    }
}
