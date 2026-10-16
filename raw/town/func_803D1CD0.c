#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80018824(u8 *, M2C_UNK);               /* extern */
extern M2C_UNK D_80016050;
extern M2C_UNK D_80016078;

s32 func_80018CD0(s32 *arg0) {
    u8 sp10;
    s32 *var_s0;
    s32 temp_s2;
    s32 temp_v0;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_v0;
    u32 var_v0_2;

    var_s0 = arg0;
    temp_s2 = M2C_FIELD(*(void **)0x80016000, s32 *, 0x38) + 0x248;
    func_80018824(&sp10, 0x14);
    if (*var_s0 != 0) {
        var_v0_2 = *var_s0 - temp_s2;
        do {
            if ((&sp10)[var_v0_2 >> 2] != 0) {
                M2C_FIELD(M2C_FIELD(*(void *)0x80016000, void **, 0x20), M2C_UNK (**)(M2C_UNK *, M2C_UNK *, M2C_UNK), 0x168)(&D_80016050, &D_80016078, 0x71);
                M2C_FIELD(M2C_FIELD(*(void *)0x80016000, void **, 0x20), M2C_UNK (**)(M2C_UNK), 0x174)(1);
            }
            (&sp10)[(u32) (*var_s0 - temp_s2) >> 2] = 1;
            var_s0 += 4;
            temp_v0 = *var_s0;
            var_v0_2 = temp_v0 - temp_s2;
        } while (temp_v0 != 0);
    }
    var_s1 = 0;
    if (sp10 != 0) {
        var_s1_2 = 1;
        do {
            var_s1_2 += 1;
        } while ((&sp10)[var_s1_2] != 0);
        var_s1 = var_s1_2 - 1;
    }
    var_v0 = var_s1 * 4;
    if (var_s1 >= 0x14) {
        M2C_FIELD(M2C_FIELD(*(void *)0x80016000, void **, 0x20), M2C_UNK (**)(M2C_UNK *, M2C_UNK *, M2C_UNK), 0x168)(&D_80016050, &D_80016078, 0x76);
        M2C_FIELD(M2C_FIELD(*(void *)0x80016000, void **, 0x20), M2C_UNK (**)(M2C_UNK), 0x174)(1);
        var_v0 = var_s1 * 4;
    }
    return temp_s2 + var_v0;
}
