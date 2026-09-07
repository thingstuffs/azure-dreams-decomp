#include "common.h"

extern s32 D_800814A0[3];

void func_81898824(void *arg0, void *arg1, void *arg2)
{
    u16 temp_v0;
    void *temp_v1;

    temp_v1 = *(void **)((s8 *)arg0 + 0xC);
    *(u16 *)((s8 *)temp_v1 + 0x14) =
        (u16)(*(u16 *)((s8 *)temp_v1 + 0x14) + 1);
    *(s32 *)((s8 *)arg1 + 0x00) =
        *(s32 *)((s8 *)arg1 + 0x00) + *(s32 *)((s8 *)arg1 + 0x0C);
    *(s32 *)((s8 *)arg1 + 0x04) =
        *(s32 *)((s8 *)arg1 + 0x04) + *(s32 *)((s8 *)arg1 + 0x10);
    *(s32 *)((s8 *)arg1 + 0x08) =
        *(s32 *)((s8 *)arg1 + 0x08) + *(s32 *)((s8 *)arg1 + 0x14);
    *(u16 *)((s8 *)arg2 + 0x1A) =
        (u16)(*(u16 *)((s8 *)arg2 + 0x1A) + 0x300);
    temp_v0 = *(u16 *)((s8 *)arg0 + 0x10) + 1;
    *(u16 *)((s8 *)arg0 + 0x10) = temp_v0;
    if (*(s16 *)((s8 *)arg0 + 0x12) < (s16)temp_v0) {
        *(u16 *)((s8 *)arg0 - 2) =
            (u16)(*(u16 *)((s8 *)arg0 - 2) | 0x8000);
        D_800814A0[0] |= 0x8000;
    }
}
