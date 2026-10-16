#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80016050;
extern M2C_UNK D_80016078;

void func_80018AC4(void *arg0) {
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 temp_v0;
    s32 var_v0;
    void *temp_a1;
    void *temp_v0_2;
    void *temp_v1;

    temp_a1 = *(void **)0x80016000;
    temp_v0 = M2C_FIELD(temp_a1, s32 *, 0x38);
    temp_s1 = temp_v0 + 0x2F0;
    temp_s0 = M2C_FIELD(arg0, u8 *, 3) & 0x1F;
    var_v0 = temp_s0 * 4;
    if (M2C_FIELD(arg0, u8 *, 0) != M2C_FIELD(((temp_s0 * 0x54) + temp_s1), u8 *, 0x13)) {
        M2C_FIELD(M2C_FIELD(temp_a1, void **, 0x20), M2C_UNK (**)(M2C_UNK *, M2C_UNK *, M2C_UNK), 0x168)(&D_80016050, &D_80016078, 0x41);
        M2C_FIELD(M2C_FIELD(*(void **)0x80016000, void **, 0x20), M2C_UNK (**)(M2C_UNK), 0x174)(1);
        var_v0 = temp_s0 * 4;
    }
    temp_v0_2 = ((((var_v0 + temp_s0) * 4) + temp_s0) * 4) + temp_s1;
    M2C_FIELD(temp_v0_2, s8 *, 0x13) = 0;
    temp_s0_2 = M2C_FIELD(temp_v0_2, u8 *, 0x43) & 0x3F;
    temp_v1 = temp_v0 + (temp_s0_2 * 4);
    M2C_FIELD(temp_v1, s8 *, 0x980) = 0;
    M2C_FIELD(temp_v1, s8 *, 0x981) = 0;
    M2C_FIELD((temp_v0 + (temp_s0_2 * 0x54)), s8 *, 0xA93) = 0;
}
