#include "common.h"
#include "m2c_compat.h"

extern s32 D_800188C8;

void func_800167F0(void) {
    void *temp_a0;

    temp_a0 = M2C_FIELD(*(void **)0x80016000, void **, 0x38);
    M2C_FIELD(temp_a0, s32 *, 0x2D5C) = (s32) (M2C_FIELD(temp_a0, s32 *, 0x2D5C) - D_800188C8);
}
