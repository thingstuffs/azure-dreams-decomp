#include "common.h"
#include "m2c_compat.h"

void func_80016D98(void) {
    void *temp_a0;
    void *temp_v1;
    void *temp_v1_2;

    temp_a0 = *(void **)0x80016000;
    temp_v1 = M2C_FIELD(temp_a0, void **, 0x1C);
    M2C_FIELD(temp_v1, s32 *, 4) = (s32) ((M2C_FIELD(temp_v1, s32 *, 4) << 6) + 0x220);
    temp_v1_2 = M2C_FIELD(temp_a0, void **, 0x1C);
    M2C_FIELD(temp_v1_2, s32 *, 8) = (s32) ((M2C_FIELD(temp_v1_2, s32 *, 8) << 6) + 0x220);
}
