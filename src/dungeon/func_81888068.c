#include "common.h"

typedef struct {
    u8 pad00[0x1A];
    u16 timer;
} Actor;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} Motion;

typedef struct {
    u8 pad00[0x0C];
    u8 red;
    u8 green;
    u8 blue;
} EffectColor;

extern u16 D_80026326[5];
extern s32 D_800814A0[3];
extern void func_800478B8(void *arg0);

__asm__(".set D_80026326, 0x80026326");

void func_80025868(Actor *arg0, Motion *arg1, EffectColor *arg2)
{
    u16 *counter = D_80026326;
    u16 timer;
    u8 red;
    u8 green;
    u8 blue;

    counter[0]++;

    arg1->x += arg1->dx;
    arg1->y += arg1->dy;
    arg1->z += arg1->dz;
    arg1->dx -= arg1->dx >> 3;
    arg1->dy -= arg1->dy >> 3;
    arg1->dz += 0x4000;

    red = arg2->red;
    green = arg2->green;
    arg2->red = red - (red >> 2);
    blue = arg2->blue;
    arg2->green = green - (green >> 2);
    arg2->blue = blue - (blue >> 2);

    func_800478B8(arg2);

    timer = arg0->timer - 1;
    arg0->timer = timer;
    if ((s16)timer <= 0) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
