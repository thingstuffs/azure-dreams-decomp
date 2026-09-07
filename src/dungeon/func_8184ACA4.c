#include "common.h"

extern s32 func_80064584(s32);
extern void func_800478B8(void *);
extern s16 D_80083228;
extern s32 D_800814A0[];

void func_800244A4(void *arg0, void *arg1, void *arg2)
{
    *(s16 *)((u8 *)arg2 + 0x1A) =
        (s16)((s32)(-((func_80064584(*(s16 *)((u8 *)arg0 + 8) - D_80083228) >> 4) << 8)) >> 8);
    *(u16 *)((u8 *)arg1 + 0xA) = *(u16 *)((u8 *)arg1 + 0xA) - 8;
    func_800478B8(arg2);
    if (*(u16 *)((u8 *)arg2 + 0x14) & 0x6000) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
