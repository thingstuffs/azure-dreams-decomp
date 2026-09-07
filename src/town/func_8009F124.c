#include "common.h"

extern void func_8008F01C(void *, s32, void *);
extern void func_8009B218(void *, s32, void *, void *);

extern s32 D_800CFD00[];
extern s32 D_800D06AC[];
extern s32 D_800D0704[];
extern s32 D_800F8C44[];

void func_8009C884(void *arg0, s32 arg1, void *arg2) {
    *(void **)((u8 *)arg2 + 8) = D_800F8C44;
    *(void **)((u8 *)arg0 + 0x80) = D_800D0704;
    func_8008F01C(arg0, arg1, D_800CFD00);
    func_8009B218(arg0, arg1, arg2, D_800D06AC);
}
