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

/* Advance motion, fade the effect, and flag expiry when its timer runs out. */
void func_8195FC60(u16 *state, Motion *motion, Effect *effect)
{
    u8 brightness;
    s16 ticks_left;

    D_80027330++;

    motion->x += motion->dx;
    motion->y += motion->dy;
    motion->z += motion->dz;
    motion->dz += 0x40000;

    effect->x += effect->dx;
    effect->y += effect->dy;

    brightness = effect->red;
    brightness = brightness - brightness / *(s16 *)((u8 *)state + 0x4C);
    effect->blue = effect->green = effect->red = brightness;

    ticks_left = state[0x26] - 1;
    state[0x26] = ticks_left;
    if ((ticks_left << 16) <= 0) {
        state[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
