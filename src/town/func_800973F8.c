#include "common.h"

/* Converts directional button flags to an angle, or -1 if no direction is held. */
s32 func_80094B58(s32 buttons) {
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
