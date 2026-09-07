#include "common.h"

extern void func_800C2E84(void *arg0, s32 arg1, void *arg2);
extern u8 D_80082660[];
extern s32 D_800C5B48[];
extern u8 D_800D54CC[];

void func_800C599C(void *arg0, s32 arg1, s32 arg2) {
    func_800C2E84(arg0, arg2, D_800D54CC);
    D_80082660[(*(s32 *)((u8 *)arg0 + 0x60)) * 8] = 0;
    *(s16 *)((u8 *)arg0 + 0x6C) = 0x10;
    *(s32 **)((u8 *)arg0 + 0x54) = D_800C5B48;
}
