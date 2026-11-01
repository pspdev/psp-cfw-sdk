
#include <string.h>
 #include <pspdisplay.h>

#include <tinyfont.h>

#define PSP_LINE_SIZE 512
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272
#define FRAMEBUFFER_SIZE (PSP_LINE_SIZE*SCREEN_HEIGHT*4)

static void* g_vram_base = (void*) (0x40000000 | 0x04000000);
static int cur_fb = 0;

static void* getVramDrawBuffer()
{
    void* vram = (void*) g_vram_base;
    if (cur_fb == 0) vram += FRAMEBUFFER_SIZE;
    return vram;
}

static unsigned int next_pow2(unsigned int v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    return v+1;
}

void tinyFontSwapBuffers(){
    cur_fb ^= 1;
}

void tinyFontPrintTextScreen(
    u8* font,
    int x,
    int y,
    const char* text,
    u32 color,
    TinyFontState* state
) {
    tinyFontPrintTextBuffer(getVramDrawBuffer(), SCREEN_WIDTH, SCREEN_HEIGHT, PSP_LINE_SIZE, font, x, y, text, color, state);
}

void tinyFontPrintTextScreenBuf(
    void* framebuf,
    u8* font,
    int x,
    int y,
    const char* text,
    u32 color,
    TinyFontState* state
){
    tinyFontPrintTextBuffer(framebuf, SCREEN_WIDTH, SCREEN_HEIGHT, PSP_LINE_SIZE, font, x, y, text, color, state);
}

void tinyFontPrintTextImage(
    void* image,
    int img_w,
    int img_h,
    u8* font,
    int x,
    int y,
    const char* text,
    u32 color,
    TinyFontState* state
){
    tinyFontPrintTextBuffer(image, img_w, img_h, next_pow2(img_w), font, x, y, text, color, state);
}

void tinyFontPrintTextBuffer(
    u32* buffer,
    int buf_w,
    int buf_h,
    int pow2_w,
    u8* font,
    int x,
    int y,
    const char* text,
    u32 color,
    TinyFontState* state
){
    int c, i, j;
    u8 *font_ptr;
    u32 *vram_ptr;
    u32 *vram;
    u32 bgcolor = 0xFF000000; // shadow color

    if (state){
        if (state->scroll){
            if (state->sk) state->sk--;
            else {
                state->sx--;
                if (state->sx < state->ix) {
                    state->ci++;
                    state->sx = state->ix + 8;
                    if (state->ci >= strlen(text)){
                        state->ci = 0;
                        state->sk = 200;
                        state->sx = state->ix;
                    }
                }
                if (state->ci < strlen(text)-1) text += state->ci;
                else {
                    state->sk = 200;
                    state->ci = 0;
                    return;
                }
            }
        }
        if (state->glow){
            if (state->sc >= 250) state->sd = 0;
            else if (state->sc <= 5) state->sd = 1;

            if (state->sd) state->sc += 5;
            else state->sc -= 5;

            bgcolor |= (state->sc<<16) | (state->sc<<8) | (state->sc);
        }
    }

    for (c = 0; text[c]; c++) {
        if (x < 0 || x + 8 > buf_w || y < 0 || y + 8 > buf_h) break;
        u8 ch = (u8)text[c];
        vram = buffer + x + y * pow2_w;
        
        font_ptr = &font[ ((unsigned)ch) * 8];
        for (i = 0; i < 8; i++, font_ptr++) {
            u8 row = *font_ptr;
            vram_ptr  = vram;
            u32* prev_pixel = vram - pow2_w;
            u32* post_pixel = vram + pow2_w;
            for (j = 0; j < 8; j++, row <<= 1, vram_ptr++, prev_pixel++, post_pixel++) {
                if (row & 0x80) {
                    *vram_ptr = color;
                    // horizontal shadow
                    if (vram_ptr[-1] != color) vram_ptr[-1] = bgcolor;
                    vram_ptr[1] = bgcolor;
                    // vertical shadow
                    if (*prev_pixel != color) *prev_pixel = bgcolor;
                    *post_pixel = bgcolor;
                }
            }
            vram += pow2_w;
        }
        x += 8;
    }
}
