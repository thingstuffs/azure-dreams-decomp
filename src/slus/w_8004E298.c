#include "common.h"

extern void func_8004E264(void *a0, s32 a1);
extern u8 *func_8004E280(u8 *a0, s32 *a1);
extern void *func_8004E188(void *a0, s32 a1);

/* Builds positioned glyph records from text and embedded formatting commands. */
void *func_8004E298(u8 *glyph_buf, u8 *text, s32 style)
{
    u8 *first_glyph;
    s32 x;
    s32 y;
    s32 spacing;
    s32 x_offset;
    s32 text_byte;
    s32 char_code;
    x = 0;
    y = 0;
    first_glyph = glyph_buf;
    spacing = 0;
    text_byte = *text;
    if (text_byte != 0) {
        do {
            char_code = text_byte & 0xFF;
            if (char_code == 0x20) {
                text += 1;
                {
                    s32 space_x = x + 8;
                    x = space_x + spacing;
                }
            }
            else if (char_code == 0xA) {
                text += 1;
                x = 0;
                y = y + 8;
            }
            else if (char_code == 0x9) {
                text += 1;
                if ((*text) == 0x73) {
                    text += 1;
                    spacing = (*text) - 0x30;
                }
                else {
                    x += ((*text) - 0x30) * (spacing + 8);
                }
                text += 1;
            }
            else if (char_code == 0x8) {
                text = func_8004E280(text + 1, &style);
            }
            else if (char_code == 0xC) {
                u8 *next_text;
                next_text = func_8004E280(text + 1, &x_offset);
                x += x_offset;
                text = next_text;
            }
            else {
                s8 draw_code;
                s32 glyph_width;
                *glyph_buf = 0;
                draw_code = 0x2C;
                if (style & 0x80) {
                    draw_code = 0x2E;
                }
                glyph_buf[2] = (u8) (x - 0x80);
                glyph_buf[1] = (u8) draw_code;
                glyph_buf[3] = (u8) (y - 0x80);
                *((s16 *) (glyph_buf + 4)) = (s16) (((style & 0x300) >> 3) | 0xF);
                func_8004E264(glyph_buf, style);
                func_8004E188(glyph_buf, *text);
                text += 1;
                glyph_width = glyph_buf[10];
                glyph_buf += 0xC;
                x += glyph_width + spacing;
            }
            text_byte = *text;
        }
        while (text_byte != 0);
    }
    if (glyph_buf != first_glyph) {
        glyph_buf[-0xC] = glyph_buf[-0xC] | 0x80;
    }
    else {
        first_glyph = 0;
    }
    return first_glyph;
}
