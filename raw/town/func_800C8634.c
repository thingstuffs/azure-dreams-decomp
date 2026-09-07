#include "common.h"

extern void func_800C2E84(void *arg0, s32 arg2, void *p);
extern void func_800C6270(s32 arg1);
extern u8 D_80082660;
extern u8 D_800C5D38;
extern u8 D_800D5598;

void func_800C5D94(void *arg0, s32 arg1, s32 arg2) {
    func_800C2E84(arg0, arg2, &D_800D5598);
    *(((*(s32 *)((u8 *)arg0 + 0x60)) * 8) + &D_80082660) = 0;
    *(u8 **)((u8 *)arg0 + 0x54) = &D_800C5D38;
    func_800C6270(arg1);
}
