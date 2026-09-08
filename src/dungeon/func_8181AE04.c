#include "common.h"

extern s32 rand(void);
extern s16 func_800BCB04(u16, u16, s16);
extern s16 D_80025914;
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s32 D_800814A0[];

/* Applies randomized movement and reduces speed, setting flags when speed runs out. */
void func_8181AE04(void *object_data, s16 *position)
{
    s16 *object = object_data;
    s16 speed;
    s32 delta_x;
    s32 delta_y;

    D_80025914 = 1;
    if (position[5] < func_800BCB04((u16)position[1], (u16)position[3], position[5] + 2)) {
        delta_x = ((D_8006CCD8[object[10]] * object[25]) << 10) +
            (rand() & 0xFFFF);
        ((s32 *)position)[0] += delta_x;

        delta_y = ((D_8006CCE8[object[10]] * object[25]) << 10) +
            (rand() & 0xFFFF);
        ((s32 *)position)[1] += delta_y;
        ((s32 *)position)[2] += 0x20000 + (rand() & 0xFFF);
    }

    speed = (u16)object[25] - 8;
    object[25] = speed;
    if ((speed << 16) <= 0) {
        ((u16 *)object)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
