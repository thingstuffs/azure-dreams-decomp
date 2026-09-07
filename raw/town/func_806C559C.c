#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK D_80016000;

void func_8001659C(void) {
    void *temp_v1;
    void *temp_v1_2;
    void *temp_v1_3;
    void *temp_v1_4;

    M2C_FIELD(M2C_FIELD(M2C_FIELD(&D_80016000, void **, 0), void **, 0x20), M2C_UNK (**)(M2C_UNK), 0x248)(0);
    temp_v1 = M2C_FIELD(M2C_FIELD(&D_80016000, void **, 0), void **, 0x1C);
    M2C_FIELD(temp_v1, s32 *, 0x10) = (s32) M2C_FIELD(temp_v1, s32 *, 4);
    temp_v1_2 = M2C_FIELD(M2C_FIELD(&D_80016000, void **, 0), void **, 0x1C);
    M2C_FIELD(temp_v1_2, s32 *, 0x14) = (s32) (M2C_FIELD(temp_v1_2, s32 *, 8) + 0x20);
    M2C_FIELD(M2C_FIELD(M2C_FIELD(&D_80016000, void **, 0), void **, 0x20), M2C_UNK (**)(M2C_UNK), 0x258)(0xD);
    temp_v1_3 = M2C_FIELD(M2C_FIELD(&D_80016000, void **, 0), void **, 0x1C);
    M2C_FIELD(temp_v1_3, s32 *, 0x18) = (s32) M2C_FIELD(temp_v1_3, s32 *, 4);
    temp_v1_4 = M2C_FIELD(M2C_FIELD(&D_80016000, void **, 0), void **, 0x1C);
    M2C_FIELD(temp_v1_4, s32 *, 0x1C) = (s32) M2C_FIELD(temp_v1_4, s32 *, 8);
}
