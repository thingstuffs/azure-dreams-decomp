#include "common.h"

extern s32 func_8009A350(s16, s16, s16, u16 *);
extern s16 func_800D0DE0(s16, s16, s16);
extern void func_800D1304(s16, s16, s32, s32);

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern u8 D_8008333C[32];

s32 func_800D112C(s16 arg0, s32 arg1, s32 arg2) {
    struct {
        u16 flags;
        u16 pad;
        s32 byte_offset;
        u16 *x_step;
    } work;
    s32 direction;
    register s32 byte_offset;
    u8 *x_base;
    u16 *x_step;
    u8 *bounds;
    s16 x_acc;
    s16 y_acc;
    s16 x;
    s16 y;
    s32 remaining;
    s32 count;

    remaining = 11;
    direction = arg0;
    x_base = (u8 *)D_8006CCD8;
    byte_offset = direction * 2;
    x_step = (u16 *)(x_base + byte_offset);
    count = 0;
    x_acc = arg1 - *x_step;
    x = (u16)x_acc;
    bounds = D_8008333C;

    if (x < 0 || x >= (1 << *(s16 *)(bounds + 0x14))) {
        func_800D1304(direction, x, arg2, byte_offset);
        return 0;
    }

    {
        u8 *y_base;
        u16 *y_step;

        y_base = (u8 *)D_8006CCE8;
        y_step = (u16 *)(y_base + byte_offset);
        y_acc = arg2 - *y_step;
    }
    y = (s16)y_acc;
    if (y < 0) {
        return 0;
    }
    if (y >= (1 << *(s16 *)(bounds + 0x16))) {
        func_800D1304(direction, x, arg2, byte_offset);
        return 0;
    }

    work.byte_offset = byte_offset;
    work.x_step = x_step;
    do {
        x = (s16)x_acc;
        y = (s16)y_acc;
        if ((func_8009A350(x, y, direction, &work.flags) << 16) != 0 &&
            (work.flags & 4)) {
            count++;
            if (func_800D0DE0(direction, x, y) >= 2) {
                break;
            }
        }

        {
            register u16 *loop_x_step ASM_REG("$10");   /* MATCH pin: load-bearing for the whole function shape */

            loop_x_step = work.x_step;
            x_acc += *loop_x_step;
        }
        x = (s16)x_acc;
        if (x < 0 || x >= (1 << *(s16 *)(bounds + 0x14))) {
            break;
        }

        {
            register u8 *loop_y_base ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
            register s32 loop_byte_offset ASM_REG("$10");   /* MATCH pin: load-bearing for the whole function shape */
            u16 *loop_y_step;

            loop_y_base = (u8 *)D_8006CCE8;
            loop_byte_offset = work.byte_offset;
            loop_y_step = (u16 *)(loop_y_base + loop_byte_offset);
            y_acc += *loop_y_step;
        }
        y = (s16)y_acc;
        if (y < 0 || y >= (1 << *(s16 *)(bounds + 0x16))) {
            break;
        }
    } while (--remaining > 0);

    return (s16)count;
}
