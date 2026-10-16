#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80016FA8;
extern M2C_UNK D_8001713C;
extern M2C_UNK D_80017148;
extern M2C_UNK D_8001714C;
extern M2C_UNK D_80017154;
extern M2C_UNK D_80017160;

void *func_800184E0(s32 arg0, s32 arg1, s32 arg2) {
    s16 temp_s4;
    s32 temp_s5;
    s32 temp_v0;
    s32 var_s3;
    u8 temp_s2;
    void *temp_a0;
    void *temp_s0;
    void *temp_v1;

    var_s3 = arg1;
    if (arg0 >= 0xA) {
        return NULL;
    }
    temp_v1 = (((arg0 * 3) + arg2) * 8) + &D_80016FA8;
    temp_s4 = M2C_FIELD(temp_v1, s16 *, 0);
    temp_a0 = *(void **)0x80016000;
    temp_s2 = M2C_FIELD((M2C_FIELD(temp_a0, s32 *, 0x38) + arg0), u8 *, 0x3700);
    temp_s5 = M2C_FIELD(temp_v1, s32 *, 4);
    M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x20), M2C_UNK (**)(M2C_UNK *, M2C_UNK *, s32, s32), 0x168)(&D_8001713C, &D_80017148, var_s3, arg0);
    M2C_FIELD(M2C_FIELD(*(void **)0x80016000, void **, 0x20), M2C_UNK (**)(M2C_UNK *, M2C_UNK *, u8), 0x168)(&D_8001713C, &D_8001714C, temp_s2);
    temp_v0 = var_s3 - temp_s2;
    if (temp_s4 != 0) {
        if (temp_v0 >= 0) {
            var_s3 = temp_s4 - (temp_v0 + 1);
        } else {
            var_s3 = (temp_s2 - var_s3) - 1;
        }
    }
    M2C_FIELD(M2C_FIELD(*(void *)0x80016000, void **, 0x20), M2C_UNK (**)(M2C_UNK *, M2C_UNK *, s32), 0x168)(&D_8001713C, &D_80017148, var_s3);
    temp_s0 = (var_s3 * 8) + temp_s5;
    M2C_FIELD(M2C_FIELD(*(void *)0x80016000, void **, 0x20), M2C_UNK (**)(M2C_UNK *, M2C_UNK *, s16), 0x168)(&D_8001713C, &D_80017154, M2C_FIELD(temp_s0, s16 *, 0));
    M2C_FIELD(M2C_FIELD(*(void *)0x80016000, void **, 0x20), M2C_UNK (**)(M2C_UNK *, M2C_UNK *, s16), 0x168)(&D_8001713C, &D_80017160, M2C_FIELD(temp_s0, s16 *, 2));
    return temp_s0;
}
