#include "common.h"

extern s16 D_80025914[5];
extern s32 D_800814A0[3];

/* Advances the timer, ramps target values, and flags completion on timeout or target status. */
void func_8181B314(void *state_data, s32 unused, void *target) {
    u16 timer;
    u8 *state = state_data;

    timer = *(u16 *)(state + 2) + 2;
    D_80025914[0] = 1;
    *(u16 *)(state + 2) = timer;
    if ((s16)timer < 40) {
        *(s16 *)((u8 *)target + 0x1C) = (s16)timer * 204;
        *(s16 *)((u8 *)target + 0x1E) =
            (s16)*(u16 *)(state + 2) * 204;
    }
    if ((s16)*(u16 *)(state + 2) >= 120) {
        *(u16 *)(state - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
    if (*(u16 *)((u8 *)target + 0x14) & 0x8000) {
        *(u16 *)(state - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
