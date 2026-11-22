#include "common.h"
#include "dungeon/menu.h"
#include "sdk/libgpu.h"
#include "slus.h"
#include "dungeon/data.h"

typedef struct {
    s16 first;
    s16 second;
    s16 third;
    s16 fourth;
} DrawRecord;

/* Draws the first formatted number with 4-by-16 HUD glyphs and mode-dependent padding. */
void draw_hud_number_tall(s32 first_number, s32 second_number, u16 width, s16 y, u16 x, s16 mode)
{
    DrawRecord record;
    char first_buf[16];
    char second_buf[16];
    u8 *char_ptr;
    s16 fill_mode;

    char_ptr = (u8 *)first_buf;
    format_reversed_decimal_space_padded(first_number, width, first_buf);
    format_reversed_decimal_space_padded(second_number, width, second_buf);
    if (first_buf[0] != 0) {
        fill_mode = mode;
        do {
            u8 character;

            if (fill_mode != 0 &&
                (numeric_character_flags[character = *char_ptr] & 4) == 0) {
                record.first = 0x1C0;
            } else if (fill_mode != 0 ||
                       (numeric_character_flags[character = *char_ptr] & 4) != 0) {
                record.first = (character << 2) + 0x100;
            } else {
                record.first = 0x1EC;
            }
            record.second = 0x1B0;
            record.third = 4;
            record.fourth = 16;
            MoveImage(&record, y, (s16)x);
            char_ptr++;
            y -= 4;
        } while (*char_ptr != 0);
    }
}
