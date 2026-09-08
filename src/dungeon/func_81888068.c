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

/* Advance and fade the effect, flagging expiration when its timer runs out. */
void func_80025868(Actor *actor, Motion *motion, EffectColor *color)
{
    u16 *counter = D_80026326;
    u16 timer;
    u8 red;
    u8 green;
    u8 blue;

    counter[0]++;

    motion->x += motion->dx;
    motion->y += motion->dy;
    motion->z += motion->dz;
    motion->dx -= motion->dx >> 3;
    motion->dy -= motion->dy >> 3;
    motion->dz += 0x4000;

    red = color->red;
    green = color->green;
    color->red = red - (red >> 2);
    blue = color->blue;
    color->green = green - (green >> 2);
    color->blue = blue - (blue >> 2);

    func_800478B8(color);

    timer = actor->timer - 1;
    actor->timer = timer;
    if ((s16)timer <= 0) {
        *(u16 *)((u8 *)actor - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
