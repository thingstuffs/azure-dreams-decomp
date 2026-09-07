#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK D_80016000;
extern s32 D_80019158;

void func_8051E954(s32 arg0) {
    register s32 *temp_s0 ASM_REG("$16");
    void *temp_v1;
    s32 temp_a0;
    s32 temp_a0_2;

    temp_a0 = (arg0 & 0xFFFF) | 0x06800000;
    D_80019158 = temp_a0;
    temp_a0_2 = (temp_a0 & 0xFFFF) | 0x05000000;
    temp_s0 = &D_80019158;
    M2C_FIELD(temp_s0, s32 *, 4) = temp_a0_2;
    arg0 = (temp_a0_2 & 0xFFFF) | 0xFF000000;
    temp_v1 = M2C_FIELD(&D_80016000, void **, 0);
    M2C_FIELD(temp_s0, s32 *, 8) = arg0;
    M2C_FIELD(M2C_FIELD(temp_v1, void **, 0x20), M2C_UNK (**)(M2C_UNK), 0x208)(0);
    M2C_FIELD(M2C_FIELD(M2C_FIELD(&D_80016000, void **, 0), void **, 0x20), M2C_UNK (**)(s32 *), 0x224)(temp_s0);
}
