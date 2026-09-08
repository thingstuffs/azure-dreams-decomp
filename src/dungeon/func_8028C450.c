#include "common.h"

extern void func_8001F354(s32, s32, s32, void *);
extern void func_8004E634(s16, u8 *);

extern s32 D_80012090[];
extern void *D_8001F5B4[];
extern u8 D_80077DE8[];
extern u8 D_80077E00[];
extern s16 D_8008146C;

/* Draw the current value and its label, using a special label when needed. */
void func_8001F450(void)
{
    u8 digits[2];
    u8 *digit_ptr;
    void *special_label;
    s32 draw_mode;
    register s16 draw_x ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 draw_y_fixed;
    s32 blank_code;
    u8 digit;
    special_label = 0;
    if (*(s32 *)0x80012090 != 2) {
        if (D_8008146C == 0x28) {
            special_label = D_80077E00;
        }
        draw_mode = 0;
    } else {
        draw_mode = 1;
    }

    if (special_label != 0) {
        func_8001F354(0xAA, 0x78, 0, special_label);
        return;
    }

    func_8001F354(0xAA, 0x78, draw_mode, D_80077DE8);
    digit_ptr = digits;
    func_8004E634(D_8008146C, digit_ptr);

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
                func_8001F354(draw_x, draw_y_fixed >> 16, draw_mode, D_8001F5B4[digit]);
            }
            digit_ptr++;
            draw_x += 0x12;
        } while (*digit_ptr != 0);
    }
}
