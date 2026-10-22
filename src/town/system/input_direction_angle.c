/* Input direction angle and its file-private helper. */
#include "common.h"
#include "shared/game_work.h"
static s32 directional_buttons_to_angle(s32);

/* Converts directional button bits to an eight-way angle, returning -1 when no direction is held. */
static s32 directional_buttons_to_angle(s32 buttons) {
    if (buttons & 0x1000) {
        s32 left_flag;
        s32 right_flag;

        left_flag = buttons & 0x8000;
        if (left_flag != 0) {
            return 0xA00;
        }
        right_flag = buttons & 0x2000;
        if (right_flag != 0) {
            return 0x600;
        }
        return 0x800;
    } else {
        s32 direction_flag;

        direction_flag = buttons & 0x4000;
        if (direction_flag != 0) {
            direction_flag = buttons & 0x8000;
            if (direction_flag != 0) {
                return 0xE00;
            }
            direction_flag = buttons & 0x2000;
            direction_flag = direction_flag != 0;
            return direction_flag << 9;
        } else {
            direction_flag = buttons & 0x8000;
            if (direction_flag != 0) {
                return 0xC00;
            }
            if (buttons & 0x2000) {
                return 0x400;
            }
            return -1;
        }
    }
}

s32 input_angle_with_offset(s32 unused, s32 angle_offset) {
    s32 base_angle;

    base_angle = directional_buttons_to_angle(g_game_work.buttons);
    if ((s16)base_angle == -1) {
        return -1;
    }
    return (base_angle + angle_offset) & 0xFFF;
}
