#include "common.h"
#include "m2c_compat.h"

extern s8 D_80083160[];
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
s32 func_80044724();
M2C_UNK func_800D112C();
M2C_UNK func_800D1338();

typedef struct S_800D13B8_0 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_800D13B8_0;   /* temp_s0_1 in func_800D13B8 */

typedef struct S_800D13B8_1 {
    u8 pad_00[0xA4];
    u16 unk_A4;
    u16 unk_A6;
} S_800D13B8_1;   /* temp_s1 in func_800D13B8 */

/* Processes directions around the current position based on the facing angle. */
void func_800D13B8(void) {
    s8 *state;
    register s8 *direction_work ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    s16 coord_x;
    s16 coord_y;
    s32 facing;
    s32 direction;
    register s32 left_direction ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 diagonal_x;
    s16 diagonal_y;
    s32 next_direction;
    s32 offset_x_high;
    register s32 last_direction ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 last_x;
    s32 last_y;
    s32 last_x_high;
    s32 last_y_high;
    s32 axis_step;
    u16 *x_step;
    u16 *diagonal_x_step;

    state = D_80083160;
    direction_work = state + 0x18;
    if (func_80044724() != 0) {
        facing = 2 - ((s32) (((S_800D13B8_0 *)state)->unk_C8 + 0x100) >> 9);
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
            diagonal_x_step = D_8006CCD8;
            diagonal_x_step = &diagonal_x_step[direction];
            func_800D112C(next_direction, (u32) (s16) (diagonal_x + ((s16) *diagonal_x_step * 0xA)), (u32) (s16) (diagonal_y + ((s16) D_8006CCE8[direction] * 0xA)));
            last_direction = (direction - 3) & 7;
            last_x = (s16) (diagonal_x + ((s16) *diagonal_x_step * 0xA));
            last_y = (s16) (diagonal_y + ((s16) D_8006CCE8[direction] * 0xA));
        } else {
            direction_work = (s8 *) (s32) direction;
            func_800D112C((s32) direction_work, coord_x, coord_y);
            direction = (s32) direction_work + 2;
            direction &= 7;
            func_800D112C(direction, coord_x, coord_y);
            left_direction = ((s32) direction_work - 2) & 7;
            func_800D112C(left_direction, coord_x, coord_y);
            next_direction = (s32) direction_work + 4;
            next_direction &= 7;
            x_step = D_8006CCD8;
            direction_work = (s8 *) ((s32) direction_work * 2);
            x_step = (u16 *) ((s8 *) x_step + (s32) direction_work);
            offset_x_high = (s32) ((u32) (coord_x + ((s16) *x_step * 0xA)) << 16);
            direction_work = (s8 *) D_8006CCE8 + (s32) direction_work;
            func_800D112C(next_direction, offset_x_high >> 16, (u32) (s16) (coord_y + ((s16) *(u16 *) direction_work * 0xA)));
            func_800D112C(direction, (u32) (s16) (coord_x + ((s16) *x_step * 0xA)), (u32) (s16) (coord_y + ((s16) *(u16 *) direction_work * 0xA)));
            axis_step = (s16) *x_step;
            last_direction = left_direction;
            last_x_high = (s32) ((u32) (coord_x + (axis_step * 0xA)) << 16);
            axis_step = (s16) *(u16 *) direction_work;
            last_x = last_x_high >> 16;
            last_y_high = (s32) ((u32) (coord_y + (axis_step * 0xA)) << 16);
            last_y = last_y_high >> 16;
        }
        func_800D112C(last_direction, last_x, last_y);
    }
}
