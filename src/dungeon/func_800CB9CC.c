#include "common.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"

extern s32 func_8009A350(s16, s16, s16, u16 *);
extern s16 func_800D0DE0(s16, s16, s16);

/* Counts flagged tiles along a direction for up to eleven steps. */
s32 func_800D112C(s16 scan_direction, s32 start_x, s32 start_y) {
    s32 bound_bit;
    u16 flags;
    s32 saved_offset;
    u16 *saved_x_step;
    u16 *y_step;
    s32 direction;
    register s32 byte_offset;
    u8 *x_base;
    u16 *x_step;
    MapGrid *bounds;
    s16 x_acc;
    s16 y_acc;
    s16 x;
    s16 y;
    s32 remaining;
    s32 count;

    remaining = 11;
    direction = scan_direction;
    x_base = (u8 *)dirStepX;
    byte_offset = direction * 2;
    x_step = (u16 *)(x_base + byte_offset);
    count = 0;
    x_acc = start_x - *x_step;
    x = (u16)x_acc;
    bounds = &gameWork.map;

    if (x < 0 || x >= ((bound_bit = 1) << bounds->shiftX)) {
        return 0;
    }

    {
        u8 *y_base;

        y_base = (u8 *)dirStepY;
        y_step = (u16 *)(y_base + byte_offset);
        y_acc = start_y - *y_step;
    }
    y = (s16)y_acc;
    if (y < 0) {
        return 0;
    }
    if (y >= (bound_bit << bounds->shiftY)) {
        return 0;
    }

    saved_offset = byte_offset;
    saved_x_step = x_step;
    do {
        u16 *loop_x_step;
        x = (s16)x_acc;
        y = (s16)y_acc;
        if ((func_8009A350(x, y, direction, &flags) << 16) != 0 &&
            (flags & 4)) {
            count++;
            if (func_800D0DE0(direction, x, y) >= 2) {
                break;
            }
        }

        {
            loop_x_step = saved_x_step;
            x_acc += *loop_x_step;
        }
        x = (s16)x_acc;
        if (x < 0 || x >= (1 << bounds->shiftX)) {
            break;
        }

        {
            u8 *loop_y_base;

            loop_y_base = (u8 *)dirStepY;
            loop_x_step = (u16 *)(saved_offset);
            loop_y_base += (s32)loop_x_step;
            y_step = (u16 *)loop_y_base;
            y_acc += *y_step;
        }
        y = (s16)y_acc;
        if (y < 0 || y >= (1 << bounds->shiftY)) {
            break;
        }
    } while (--remaining > 0);

    return (s16)count;
}
