#include "common.h"

s32 func_8004D880();                             /* extern */
void get_glyph_vram_rectangle(s32 rect_id, s16 *vram_rect);              /* extern */
void func_800673A0(void *, s32, s32);         /* extern */

typedef struct S_80123928_0 {
    u8 unk_00;
    u8 unk_01;
} S_80123928_0;

/* Outputs two-byte character codes, advancing the position by two per character. */
void draw_vram_glyph_text(u8 *text, s16 start_x, s16 y) {
    s32 glyph;
    s16 x;
    u8 *cursor;
    u8 code_hi;
    u8 code_lo;

    cursor = text;
    x = start_x;
    if (*cursor != 0) {
        do {
            code_hi = ((S_80123928_0 *)cursor)->unk_00;
            code_lo = ((S_80123928_0 *)cursor)->unk_01;
            cursor += 2;
            get_glyph_vram_rectangle(func_8004D880(code_lo | (code_hi << 8)) & 0xFF, &glyph);
            func_800673A0(&glyph, x, y);
            x += 2;
        } while (*cursor != 0);
    }
}
