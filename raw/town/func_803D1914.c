#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_8001B1C0;

M2C_UNK *func_80018914(M2C_UNK *arg0) {
    s32 *var_a3;
    void **var_t0;
    void *temp_v0;
    void *var_v0;

    *arg0 = M2C_UNALIGNED32(M2C_FIELD(&D_8001B1C0, M2C_UNK *, 0));
    temp_v0 = M2C_FIELD(*(void **)0x80016000, void **, 0x38);
    var_t0 = temp_v0 + 0x29C;
    var_a3 = arg0 + 4;
    if (M2C_FIELD(temp_v0, void **, 0x29C) != NULL) {
        var_v0 = M2C_FIELD(temp_v0, void **, 0x29C);
        do {
            M2C_FIELD(var_a3, u8 *, 0) = M2C_UNALIGNED32(M2C_FIELD(var_v0, M2C_UNK *, 0));
            if (M2C_FIELD(((M2C_FIELD(var_a3, u8 *, 0) * 0x14) + M2C_FIELD(((M2C_FIELD(var_a3, u8 *, 1) * 0x14) + M2C_FIELD(M2C_FIELD(*(void **)0x80016000, void **, 0x24), s32 *, 0x6C)), s32 *, 0xC)), s16 *, 0x12) == 0) {
                M2C_FIELD(var_a3, u8 *, 3) = (u8) (M2C_FIELD(var_a3, u8 *, 3) | 0x80);
            }
            var_t0 += 4;
            var_v0 = *var_t0;
            var_a3 += 4;
        } while (var_v0 != NULL);
    }
    *var_a3 = 0;
    return arg0;
}
