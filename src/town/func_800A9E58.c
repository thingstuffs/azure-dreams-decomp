#include "common.h"

extern void func_800A71F0(s32 arg0, void *arg1, void *arg2);
extern u8 D_800A74D8[];
extern u8 D_800D0E04[];

/* Creates an object at the given position with preset state and sprite data. */
void func_800A75B8(s32 position) {
    func_800A71F0(position, D_800A74D8, D_800D0E04);
}
