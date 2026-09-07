#include "common.h"

extern s32 D_800D0678[];
extern void func_8009C7A8(s32, s32, s32, s32, s32, s32 *);

void func_8009CB64(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_8009C7A8(arg0, arg1, arg2, arg3, arg3, D_800D0678);
}
