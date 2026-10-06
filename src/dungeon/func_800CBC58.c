#include "common.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"

s32 func_80044724();
s32 func_800D112C();
void func_800D1338();

typedef struct S_800D13B8_1 {
    u8 pad_00[0xA4];
    u16 unk_A4;
    u16 unk_A6;
} S_800D13B8_1;   /* temp_s1 in func_800D13B8 */

/* Processes directions around the current position based on the facing angle. */
void func_800D13B8(void) {
    GameWork *state;
    s8 *direction_work;
    s32 next_axis_direction;
    s32 axis_index = 0;
    u16 *y_step;
    s16 coord_x;
    s16 coord_y;
    s32 facing;
    s32 direction;
    s32 diagonal_x;
    s16 diagonal_y;
    s32 next_direction;
    s32 offset_x_high;
    s32 last_direction;
    s32 last_x;
    s32 last_y;
    s32 last_x_high;
    s32 last_y_high;
    s32 axis_step;
    u16 *x_step;
    u16 *diagonal_x_step;

    state = &gameWork;
    direction_work = (u8 *)state + 0x18;
    if (func_80044724() != 0) {
        facing = 2 - ((s32) (state->view.viewAngle + 0x100) >> 9);
        func_800D1338();
        coord_x = (u16) ((S_800D13B8_1 *)direction_work)->unk_A4 >> 6;
        coord_y = (u16) ((S_800D13B8_1 *)direction_work)->unk_A6 >> 6;
        direction = facing & 7;
        if (facing & 1) {
            diagonal_x = coord_x;
            diagonal_y = coord_y;
            func_800D112C((direction + 1) & 7, diagonal_x, diagonal_y);
            func_800D112C((direction - 1) & 7, diagonal_x, diagonal_y);
            next_direction = direction + 3;
            next_direction &= 7;
            diagonal_x_step = dirStepX;
            diagonal_x_step = &diagonal_x_step[direction];
            func_800D112C(next_direction, (u32) (s16) (diagonal_x + ((s16) *diagonal_x_step * 0xA)),
                (u32) (s16) (diagonal_y + ((s16) dirStepY[direction] * 0xA)));
            last_direction = (direction - 3) & 7;
            last_x = (s16) (diagonal_x + ((s16) *diagonal_x_step * 0xA));
            last_y = (s16) (diagonal_y + ((s16) dirStepY[direction] * 0xA));
            func_800D112C(last_direction, last_x, last_y);
        } else {
            axis_index = direction;
            func_800D112C(axis_index, coord_x, coord_y);
            next_axis_direction = axis_index + 2;
            next_axis_direction &= 7;
            func_800D112C(next_axis_direction, coord_x, coord_y);
            last_direction = axis_index - 2;
            last_direction &= 7;
            func_800D112C(last_direction, coord_x, coord_y);
            next_direction = axis_index + 4;
            next_direction &= 7;
            x_step = dirStepX;
            axis_index *= 2;
            x_step = (u16 *) ((s8 *) x_step + axis_index);
            offset_x_high = (s32) ((u32) (coord_x + ((s16) *x_step * 0xA)) << 16);
            y_step = (u16 *)((s8 *)dirStepY + axis_index);
            func_800D112C(next_direction, offset_x_high >> 16, (u32) (s16) (coord_y
                + ((s16) *y_step * 0xA)));
            func_800D112C(next_axis_direction, (u32) (s16) (coord_x + ((s16) *x_step * 0xA)),
                (u32) (s16) (coord_y + ((s16) *y_step * 0xA)));
            last_x_high = (s32)((u32)(coord_x + (s16)*x_step * 0xA) << 16);
            axis_step = (s16) *y_step;
            last_x = last_x_high >> 16;
            last_y_high = (s32) ((u32) (coord_y + (axis_step * 0xA)) << 16);
            last_y = last_y_high >> 16;
            func_800D112C(last_direction, last_x, last_y);
        }
    }
}
