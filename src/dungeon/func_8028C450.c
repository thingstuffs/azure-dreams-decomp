#include "modules/dungeon_floor_spawns.h"

void draw_dungeon_value_and_label(void)
{
    u8 digits[2];
    u8 *digit_ptr;
    void *special_label;
    s32 draw_mode;
    s16 draw_x;
    s32 draw_y_fixed;
    s32 blank_code;
    u8 digit;
    special_label = 0;
    if (*(s32 *)0x80012090 != 2) {
        if ((*(s16 *)D_8008146C) == 0x28) {
            special_label = D_80077E00;
        }
        draw_mode = 0;
    } else {
        draw_mode = 1;
    }

    if (special_label != 0) {
        create_tinted_dungeon_object(0xAA, 0x78, 0, special_label);
        return;
    }

    create_tinted_dungeon_object(0xAA, 0x78, draw_mode, D_80077DE8);
    do {
        digit_ptr = digits;
    } while (0);
    func_8004E634((*(s16 *)D_8008146C), digit_ptr);

    draw_x = 0xC8;
    if (digits[1] == 0) {
        draw_x = 0xDA;
    }

    if (digits[0] != 0) {
        blank_code = 0x20;
        draw_y_fixed = 0x780000;
        do {
            digit = *digit_ptr;
            if (digit != blank_code) {
                create_tinted_dungeon_object(draw_x, draw_y_fixed >> 16, draw_mode, D_8001F5B4[digit]);
            }
            digit_ptr++;
            draw_x += 0x12;
        } while (*digit_ptr != 0);
    }
}
