#include "common.h"

extern s16 D_8002571C[5];
extern s32 D_800814A0[3];

void func_800248B8(void *arg0, s32 arg1, void *arg2)
{
    s32 timer;

    *(u16 *)((u8 *)arg0 + 0x2A) =
        (u16)(*(u16 *)((u8 *)arg0 + 0x2A) - 1);
    *(u16 *)((u8 *)arg2 + 0x1C) =
        (u16)(*(u16 *)((u8 *)arg2 + 0x1C) + 0x320);
    *(u16 *)((u8 *)arg2 + 0x1E) =
        (u16)(*(u16 *)((u8 *)arg2 + 0x1E) + 0x320);
    *(u16 *)((u8 *)arg2 + 0x1A) =
        (u16)(*(u16 *)((u8 *)arg2 + 0x1A) + 0x190);
    timer = *(s16 *)((u8 *)arg0 + 0x2A);
    D_8002571C[0] = 1;
    if (timer <= 0) {
        *(u16 *)((u8 *)arg0 - 2) =
            (u16)(*(u16 *)((u8 *)arg0 - 2) | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
