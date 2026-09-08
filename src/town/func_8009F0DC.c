#include "common.h"

extern void func_8009C7A8(void *arg0, s32 arg1, s32 arg2, void *arg3, void *arg4, void *arg5);

extern s32 D_800CFD00[];
extern s32 D_800D06F8[];
extern s32 D_800F8BCC[];
extern s32 D_800F8BD8[];

/* Assign the object data table and initialize it with the shared tables. */
void func_8009C83C(void *object, s32 setup_arg1, s32 setup_arg2) {
    *(void **)((u8 *)object + 0x7C) = D_800D06F8;
    func_8009C7A8(object, setup_arg1, setup_arg2, D_800F8BCC, D_800F8BD8, D_800CFD00);
}
