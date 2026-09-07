#include "common.h"

extern void func_800C2E84(void *arg0, s32 arg1, void *arg2);
extern u8 D_80082660[];
extern u8 D_800C3BF4[];
extern u8 D_800D54DC[];
extern u8 D_800D55E8[];
extern u8 D_800D55F0[];
extern u8 D_800D5618[];
extern u8 D_800D561C[];

void func_800C5A54(void *arg0, s32 arg1, s32 arg2) {
    D_80082660[(*(s32 *)((u8 *)arg0 + 0x60)) * 8] = 0;
    *(void **)((u8 *)arg0 + 0x58) = D_800D5618;
    *(void **)((u8 *)arg0 + 0x5C) = D_800D561C;
    *(void **)((u8 *)arg0 + 0x7C) = D_800D55E8;
    *(void **)((u8 *)arg0 + 0x80) = D_800D55F0;
    func_800C2E84(arg0, arg2, D_800D54DC);
    *(void **)((u8 *)arg0 + 0x54) = D_800C3BF4;
}
