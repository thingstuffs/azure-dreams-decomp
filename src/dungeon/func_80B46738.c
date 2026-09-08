#include "common.h"

extern s32 D_800814A0[3];

/* Counts down a delay, then dims the effect color until completion. */
void func_80173F38(void *effect) {
    s16 state;
    u16 timer;

    state = *(s16 *)((u8 *)effect + 0xC);
    if (state == 0) {
        goto countdown;
    }
    if (state == 1) {
        goto fade;
    }
    return;

countdown:
    timer = *(u16 *)((u8 *)effect + 0xE) - 1;
    *(u16 *)((u8 *)effect + 0xE) = timer;
    if ((s32)(timer << 16) > 0) {
        goto done;
    }
    *(u16 *)((u8 *)effect + 0xC) += 1;
    return;

fade:
    {
        s32 *flags = D_800814A0;

        if (*(u8 *)((u8 *)effect + 8) >= 0x11) {
            goto dim_color;
        }
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        *flags |= 0x8000;
        return;
    }

dim_color:
    *(s32 *)((u8 *)effect + 8) += 0xFFEFEFF0;
done:
    return;
}
