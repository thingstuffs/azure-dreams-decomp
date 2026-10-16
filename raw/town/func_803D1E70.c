#include "common.h"
#include "m2c_compat.h"

void *func_80018CD0(void *);                        /* extern */
extern M2C_UNK D_80016050;
extern M2C_UNK D_80016078;

void func_80018E70(void *arg0) {
    s32 *var_s0_2;
    void *temp_v0;
    void *temp_v0_2;
    void *var_s0;

    temp_v0 = M2C_FIELD(*(void **)0x80016000, void **, 0x38);
    var_s0 = temp_v0 + 0x29C;
    temp_v0_2 = func_80018CD0(var_s0);
    if (temp_v0_2 == NULL) {
        M2C_FIELD(M2C_FIELD(*(void **)0x80016000, void **, 0x20), M2C_UNK (**)(M2C_UNK *, M2C_UNK *, M2C_UNK), 0x168)(&D_80016050, &D_80016078, 0x80);
        M2C_FIELD(M2C_FIELD(*(void **)0x80016000, void **, 0x20), M2C_UNK (**)(M2C_UNK), 0x174)(1);
    }
    M2C_FIELD(temp_v0_2, M2C_UNK *, 0) = M2C_UNALIGNED32(M2C_FIELD(arg0, M2C_UNK *, 0));
    M2C_FIELD(temp_v0_2, u8 *, 3) = (u8) (M2C_FIELD(temp_v0_2, u8 *, 3) & 0x5F);
    if (M2C_FIELD(temp_v0, s32 *, 0x29C) != 0) {
        var_s0_2 = var_s0 + 4;
        do {
            var_s0_2 += 4;
        } while (*var_s0_2 != 0);
        var_s0 = var_s0_2 - 4;
    }
    M2C_FIELD(var_s0, void **, 0) = temp_v0_2;
    M2C_FIELD(var_s0, s32 *, 4) = 0;
}
