#include "common.h"

extern u8 D_800D162C[];

void func_800B2394(void *arg0, s32 arg1) {
    u8 *base;
    u8 *temp_a1;

    base = D_800D162C;
    *(s32 *)((s8 *) arg0 + 0xC) = arg1;
    temp_a1 = base + arg1 * 2;
    *(s32 *)((s8 *) arg0 + 0x14) = temp_a1[0];
    *(s32 *)((s8 *) arg0 + 0x18) = temp_a1[1];
}
