#include "common.h"
#include "dungeon/menu.h"
#include "engine/camera.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 MoveImage(s32 *, s32, s32);         /* extern */

typedef struct S_80123928_0 {
    u8 unk_00;
    u8 unk_01;
} S_80123928_0;

/* Renders two-byte character codes, advancing the horizontal position by two per character. */
void draw_vram_glyph_text(u8 *text, s16 x, s16 y) {
    s32 glyph;
    s16 draw_x;
    u8 *cursor;
    u8 code_hi;
    u8 code_lo;

    cursor = text;
    draw_x = x;
    if (*cursor != 0) {
        do {
            code_hi = ((S_80123928_0 *)cursor)->unk_00;
            code_lo = ((S_80123928_0 *)cursor)->unk_01;
            cursor += 2;
            get_glyph_vram_rectangle(map_fullwidth_character_to_glyph_byte(code_lo | (code_hi << 8)) & 0xFF, &glyph);
            MoveImage(&glyph, draw_x, y);
            draw_x += 2;
        } while (*cursor != 0);
    }
}
