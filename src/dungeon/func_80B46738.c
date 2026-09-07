#include "common.h"

extern s32 D_800814A0[3];

void func_80173F38(void *arg0) {
    s16 state;
    u16 timer;

    state = *(s16 *)((u8 *)arg0 + 0xC);
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    return;

state_zero:
    timer = *(u16 *)((u8 *)arg0 + 0xE) - 1;
    *(u16 *)((u8 *)arg0 + 0xE) = timer;
    if ((s32)(timer << 16) > 0) {
        goto done;
    }
    *(u16 *)((u8 *)arg0 + 0xC) += 1;
    return;

state_one:
    {
        s32 *flags = D_800814A0;

        if (*(u8 *)((u8 *)arg0 + 8) >= 0x11) {
            goto large;
        }
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        *flags |= 0x8000;
        return;
    }

large:
    *(s32 *)((u8 *)arg0 + 8) += 0xFFEFEFF0;
done:
    return;
}
