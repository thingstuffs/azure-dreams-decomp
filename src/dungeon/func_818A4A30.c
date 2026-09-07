#include "common.h"

s32 func_800478B8();

void func_818A4A30(void **arg0, long long arg2) {
    void *temp_v1;
    u16 *temp_a0;
    u32 temp_a2;

    temp_v1 = *arg0;
    temp_a0 = (u16 *)((s8 *)temp_v1 + 0x14);
    temp_a2 = arg2;
    *temp_a0 = (u16)(*temp_a0 + 1);
    func_800478B8(temp_a2);
}
