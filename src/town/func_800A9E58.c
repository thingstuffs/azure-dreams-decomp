#include "common.h"

extern void func_800A71F0(s32 arg0, void *arg1, void *arg2);
extern u8 D_800A74D8[];
extern u8 D_800D0E04[];

void func_800A75B8(s32 arg0) {
    func_800A71F0(arg0, D_800A74D8, D_800D0E04);
}
