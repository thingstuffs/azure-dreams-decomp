#include "common.h"

extern void func_8008F0A4(void *arg0, s32 arg1, void *arg2);
extern void func_8009B218(void *arg0, s32 arg1, s32 arg2, void *arg3);
extern void func_800C2E84(void *arg0, s32 arg2, void *arg3);

extern s32 D_800CFD00[];
extern s32 D_800D11D0[];
extern s32 D_800D11EC[];
extern s32 D_800AAB20[];

void func_800AAAA0(void *arg0, s32 arg1, s32 arg2) {
    func_8008F0A4(arg0, arg1, &D_800CFD00);
    func_8009B218(arg0, arg1, arg2, &D_800D11D0);
    func_800C2E84(arg0, arg2, &D_800D11EC);
    *(void **)((s8 *)arg0 - 0x10) = &D_800AAB20;
}
