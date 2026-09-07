#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef s32 M2C_UNK;

M2C_UNK func_800DC82C();
extern s32 D_800E5910;

void func_800DC888(void) {
    s32 *temp_a2;
    s32 *temp_v1;
    s32 x;
    void *temp_a0;

    temp_a0 = D_800E5910 + 0x20;
    temp_v1 = M2C_FIELD(temp_a0, s32 **, 0x38);
    *temp_v1 += 1;
    temp_a2 = M2C_FIELD(temp_a0, s32 **, 0x38);
    x = *temp_a2;
    *temp_a2 = x % 3;
    func_800DC82C(temp_a0, x % 3, temp_a2);
}
