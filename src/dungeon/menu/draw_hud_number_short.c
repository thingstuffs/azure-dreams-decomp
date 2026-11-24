#include "common.h"
#include "dungeon/menu.h"
#include "sdk/libgpu.h"
#include "slus.h"
#include "dungeon/data.h"

/* Draws the first formatted number with 4-by-8 HUD glyphs and mode-dependent padding. */
void draw_hud_number_short(s32 first_number, s32 second_number, u16 width, s16 y, u16 x, s16 mode)
{
    RECT record;
    char first_buf[16];
    char second_buf[16];
    u8 *cursor;
    s16 padding_mode;

    cursor = (u8 *)first_buf;
    format_reversed_decimal_space_padded(first_number, width, first_buf);
    format_reversed_decimal_space_padded(second_number, width, second_buf);
    if (first_buf[0] != 0) {
        padding_mode = mode;
        do {
            s32 glyph_u;
            u8 char_code;

            if (padding_mode != 0 &&
                (numeric_character_flags[char_code = *cursor] & 4) == 0) {
                glyph_u = 0x1C0;
                record.x = glyph_u;
            } else if (padding_mode != 0 ||
                       (numeric_character_flags[char_code = *cursor] & 4) != 0) {
                glyph_u = (char_code << 2) + 0x100;
                record.x = glyph_u;
            } else {
                glyph_u = 0x1E8;
                record.x = glyph_u;
            }
            record.y = 0x1C0;
            record.w = 4;
            record.h = 8;
            MoveImage(&record, y, (s16)x);
            cursor++;
            y -= 4;
        } while (*cursor != 0);
    }
}
