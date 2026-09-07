#include "common.h"

extern void func_80096A5C(void *, u8, s8, s32);

void func_80096A30(void *arg0, u8 *arg1, s32 arg2) {
    func_80096A5C(arg0, arg1[arg2], ((s8 *)arg0)[4], 0);
}
