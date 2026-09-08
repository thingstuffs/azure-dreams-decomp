#include "common.h"

extern s32 D_800814A0[];
extern void func_80176478(void) __attribute__((noreturn));

/* Updates an effect's lifetime, fades its color, and advances its motion. */
void func_80E3CBD0(void *effect, s32 *motion, u8 *color_data)
{
    u16 ticks_left;
    u8 intensity;

    ticks_left = *(u16 *)((u8 *)effect + 0x20) - 1;
    *(u16 *)((u8 *)effect + 0x20) = ticks_left;
    if ((s16)ticks_left <= 0) {
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        func_80176478();
    }

    intensity = color_data[0xC];
    intensity -= intensity / (s16)ticks_left;
    color_data[0xC] = intensity;
    color_data[0xD] = intensity;
    color_data[0xE] = intensity;

    motion[0] += motion[3];
    motion[1] += motion[4];
    motion[2] += motion[5];
    motion[5] += 0x60000;
}
