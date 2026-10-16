#include "common.h"
#include "m2c_compat.h"

void func_80019D60(void *arg0) {
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a1;

    M2C_FIELD(M2C_FIELD(*(void **)0x80016000, void **, 0x20), M2C_UNK (**)(M2C_UNK), 0x258)(1);
    temp_a1 = *(void **)0x80016000;
    temp_a0 = M2C_FIELD(temp_a1, void **, 0x1C);
    M2C_FIELD(temp_a0, s32 *, 4) = (s32) (M2C_FIELD(temp_a0, s32 *, 4) + M2C_FIELD(arg0, s16 *, 0));
    temp_a0_2 = M2C_FIELD(temp_a1, void **, 0x1C);
    M2C_FIELD(temp_a0_2, s32 *, 8) = (s32) (M2C_FIELD(temp_a0_2, s32 *, 8) + M2C_FIELD(arg0, s16 *, 2));
}
