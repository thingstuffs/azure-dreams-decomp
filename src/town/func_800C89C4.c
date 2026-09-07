#include "common.h"

typedef s32 M2C_UNK;

extern void func_800C3050(void *arg0, s32 arg1, void *arg2, void *arg3, void *arg4, void *arg5);
extern M2C_UNK D_800D5624[];
extern M2C_UNK D_800D562C[];
extern M2C_UNK D_800D5654[];
extern M2C_UNK D_800D5658[];

void func_800C6124(void *arg0) {
    func_800C3050(arg0, 0xD, D_800D5654, D_800D5658, D_800D5624, D_800D562C);
    *((s8 *)arg0 + 0x70) = 1;
}
