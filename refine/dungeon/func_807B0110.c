#include "common.h"

extern s16 func_800BCB04(u16, u16, s16);
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s32 D_800814A0[];

/* Updates position using decaying speed and sets completion flags when speed expires. */
void func_807B0110(void *motion_data, s16 *position) {
    s16 *motion = motion_data;
    s16 next_speed;

    if (position[5] < func_800BCB04((u16) position[1], (u16) position[3], position[5] + 2)) {
        ((s32 *) position)[0] -= (D_8006CCD8[motion[10]] * motion[25]) << 11;
        ((s32 *) position)[1] -= (D_8006CCE8[motion[10]] * motion[25]) << 11;
        ((s32 *) position)[2] += (0xC0 - motion[25]) << 10;
    }

    next_speed = (u16) motion[25] - 8;
    motion[25] = next_speed;
    if ((next_speed << 16) <= 0) {
        ((u16 *) motion)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
