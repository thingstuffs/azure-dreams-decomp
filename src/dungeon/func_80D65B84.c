#include "common.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} Motion;

extern s32 D_800814A0;

/* Advance and damp motion, fade the primitive, and flag the effect when its timer expires. */
void func_80D65B84(void *effect, Motion *motion, void *primitive) {
    s32 intensity;
    s16 ticks_left;

    motion->x += motion->dx;
    motion->y += motion->dy;
    motion->z += motion->dz;
    motion->dx /= 2;
    motion->dy /= 2;
    motion->dz /= 2;

    intensity = (*(s16 *)((u8 *)effect + 0xC) << 7) /
               *(s16 *)((u8 *)effect + 0xE);
    *(s8 *)((u8 *)primitive + 0xE) = intensity;
    *(s8 *)((u8 *)primitive + 0xD) = intensity;
    *(s8 *)((u8 *)primitive + 0xC) = intensity;

    ticks_left = *(u16 *)((u8 *)effect + 0xC) - 1;
    *(s16 *)((u8 *)effect + 0xC) = ticks_left;
    if ((ticks_left << 16) <= 0) {
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
