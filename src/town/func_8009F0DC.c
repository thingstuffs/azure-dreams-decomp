#include "common.h"

extern void func_8009C7A8(void *arg0, s32 arg1, s32 arg2, void *arg3, void *arg4, void *arg5);

extern s32 D_800CFD00[];
extern s32 D_800D06F8[];
extern s32 D_800F8BCC[];
extern s32 D_800F8BD8[];

void func_8009C83C(void *arg0, s32 arg1, s32 arg2) {
    *(void **)((u8 *)arg0 + 0x7C) = D_800D06F8;
    func_8009C7A8(arg0, arg1, arg2, D_800F8BCC, D_800F8BD8, D_800CFD00);
}
