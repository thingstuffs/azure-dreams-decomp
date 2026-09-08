#include "common.h"

extern void func_800A71F0(s32 arg0, void *arg1, void *arg2);
extern u8 D_800C6180[];
extern u8 D_800ED15C[];

/* Creates an object at the given position with preset state and sprite data. */
void func_800C6270(s32 position) {
    func_800A71F0(position, D_800C6180, D_800ED15C);
}
