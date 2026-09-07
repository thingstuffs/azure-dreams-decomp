#include "common.h"

extern u32 *D_80129728[28];
extern void func_801237A4();

void func_801237E8(u8 *arg0)
{
    s32 **left;
    s32 **right;
    s32 **base;
    s32 *slot;
    s32 value;
    s32 i;
    u16 half;
    void *node;

    i = 2;
    base = (s32 **)D_80129728;
    left = base + 16;
    right = base + 2;
    do {
        slot = *right;
        right++;
        value = *slot;
        i++;
        *slot = **left;
        **left = value;
        left++;
    } while (i < 14);

    node = *(void **)((u8 *)D_80129728[8] + 4);
    half = *(u16 *)((u8 *)node + 8);
    *(u16 *)((u8 *)node + 8) =
        *(u16 *)((u8 *)*(void **)((u8 *)D_80129728[22] + 4) + 8);
    *(u16 *)((u8 *)*(void **)((u8 *)D_80129728[22] + 4) + 8) = half;

    arg0[0x16] ^= 1;
    func_801237A4(arg0, half, right, i);
}
