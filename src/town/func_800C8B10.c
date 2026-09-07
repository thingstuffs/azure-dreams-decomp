#include "common.h"

extern void func_800A71F0(s32 arg0, void *arg1, void *arg2);
extern u8 D_800C6180[];
extern u8 D_800ED15C[];

void func_800C6270(s32 arg0) {
    func_800A71F0(arg0, D_800C6180, D_800ED15C);
}
