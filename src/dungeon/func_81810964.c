#include "common.h"

extern s32 func_80026C20(s32);
extern u8 D_800294C4[];

void func_80025964(void *arg0)
{
    if (func_80026C20(*(s32 *)((u8 *)*(void **)((u8 *)arg0 + 0x18) + 0x28))) {
        **(void ***)((u8 *)*(void **)((u8 *)arg0 + 0x54) + 0x30) = 0;
        return;
    }

    **(void ***)((u8 *)*(void **)((u8 *)arg0 + 0x54) + 0x30) = D_800294C4;
}
