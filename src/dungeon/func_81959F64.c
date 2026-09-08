#include "common.h"

extern s16 func_800BCB04(u16, u16, s16);
extern u16 D_800281F8[];
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s32 D_800814A0[];

/* Update position, reduce movement speed, and flag completion when speed runs out. */
void func_81959F64(void *motion_data, s16 *position)
{
    s16 *motion = motion_data;
    s16 next_speed;
    u16 update_count = D_800281F8[0];
    u16 z = position[5];
    u16 x = position[1];
    u16 y = position[3];

    D_800281F8[0] = update_count + 1;
    if (position[5] < func_800BCB04(x, y, z + 2)) {
        ((s32 *)position)[0] -= (D_8006CCD8[motion[27]] * motion[24]) << 11;
        ((s32 *)position)[1] -= (D_8006CCE8[motion[27]] * motion[24]) << 11;
        ((s32 *)position)[2] += (0xC0 - motion[24]) << 10;
    }

    next_speed = (u16)motion[24] - 8;
    motion[24] = next_speed;
    if ((next_speed << 16) <= 0) {
        ((u16 *)motion)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
