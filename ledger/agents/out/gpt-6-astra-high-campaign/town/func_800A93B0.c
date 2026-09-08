#include "common.h"

extern s32 D_800814A0[3];

__asm__(".set func_800A6B68, 0x800A6B68");

/* Fade and enlarge the effect, marking it finished when its intensity falls below zero. */
void func_800A6B10(void *record, s32 unused, void *effect) {
    s32 intensity;
    u16 size;

    intensity = *(u8 *)((u8 *)effect + 0xE);
    intensity -= 0x10;
    if (intensity < 0) {
        *(u16 *)((u8 *)record - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }

    *(u8 *)((u8 *)effect + 0xE) = intensity;
    *(u8 *)((u8 *)effect + 0xD) = intensity;
    *(u8 *)((u8 *)effect + 0xC) = intensity;
    size = *(u16 *)((u8 *)effect + 0x20) + 0x100;
    *(u16 *)((u8 *)effect + 0x20) = size;
    *(u16 *)((u8 *)effect + 0x1E) = size;
    *(u16 *)((u8 *)effect + 0x1C) = size;
}
