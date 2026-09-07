#include "common.h"

extern void func_800478B8(void *arg0);
extern s16 D_8002992E[5];
extern s32 D_800814A0;

/* Updates effect motion and visual state, marking the effect inactive when its lifetime expires. */
void func_8002615C(void *effect, void *position, void *visual) {
    s32 accel_y;
    s32 accel_z;
    u16 frame;
    u16 ticks_left;

    *(s32 *)((u8 *)position + 0) += *(s32 *)((u8 *)effect + 0x7C);
    *(s32 *)((u8 *)position + 4) += *(s32 *)((u8 *)effect + 0x80);
    *(s32 *)((u8 *)position + 8) += *(s32 *)((u8 *)effect + 0x84);
    accel_y = *(s32 *)((u8 *)effect + 0x8C);
    accel_z = *(s32 *)((u8 *)effect + 0x90);
    *(s32 *)((u8 *)effect + 0x7C) += *(s32 *)((u8 *)effect + 0x88);
    *(s32 *)((u8 *)effect + 0x80) += accel_y;
    *(s32 *)((u8 *)effect + 0x84) += accel_z;
    *(u16 *)((u8 *)visual + 0x1C) -= 500;
    *(u16 *)((u8 *)visual + 0x1E) -= 500;
    frame = *(u16 *)((u8 *)effect + 0x2A);
    D_8002992E[0] = 1;
    frame += 1;
    *(u16 *)((u8 *)effect + 0x2A) = frame;
    if (!(frame & 1)) {
        func_800478B8(visual);
    }
    ticks_left = *(u16 *)((u8 *)effect + 0x28) - 1;
    *(u16 *)((u8 *)effect + 0x28) = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
