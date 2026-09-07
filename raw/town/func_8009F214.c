#include "common.h"

extern void func_8008F104(void *arg0, s32 arg1, void *arg2);
extern void func_8009B218(void *arg0, s32 arg1, void *arg2, void *arg3);

extern s32 D_800CFD00[];
extern s32 D_800F8CEC[];

void func_8009C974(void *arg0, s32 arg1, void *arg2) {
    *(void **)((u8 *)arg2 + 8) = D_800F8CEC;
    func_8008F104(arg0, arg1, D_800CFD00);
    func_8009B218(arg0, arg1, arg2, 0);
}
