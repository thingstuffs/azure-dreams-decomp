#include "common.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} Motion;

typedef struct {
    u8 pad0[0xC];
    u8 red;
    u8 green;
    u8 blue;
    u8 padF[7];
    u16 x;
    u16 y;
    u8 pad1A[6];
    u16 dx;
    u16 dy;
} Effect;

extern u16 D_80027330;
extern s32 D_800814A0[3];

void func_8195FC60(u16 *arg0, Motion *arg1, Effect *arg2)
{
    u8 color;
    s16 timer;

    D_80027330++;

    arg1->x += arg1->dx;
    arg1->y += arg1->dy;
    arg1->z += arg1->dz;
    arg1->dz += 0x40000;

    arg2->x += arg2->dx;
    arg2->y += arg2->dy;

    color = arg2->red;
    color = color - color / *(s16 *)((u8 *)arg0 + 0x4C);
    arg2->blue = arg2->green = arg2->red = color;

    timer = arg0[0x26] - 1;
    arg0[0x26] = timer;
    if ((timer << 16) <= 0) {
        arg0[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
