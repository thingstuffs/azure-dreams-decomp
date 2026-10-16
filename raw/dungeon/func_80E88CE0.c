#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80083780;

s32 func_801504E0(void *arg0) {
    s16 temp_v1;
    s16 temp_v1_2;
    s16 temp_v1_3;
    s16 temp_v1_4;
    s32 var_v0;

    if ((M2C_FIELD(&D_80083780, s16 *, 2) == M2C_FIELD(arg0, s16 *, 2)) && (M2C_FIELD(&D_80083780, s16 *, 6) == M2C_FIELD(arg0, s16 *, 6))) {
        return 9;
    }
    temp_v1_3 = M2C_FIELD(arg0, s16 *, 2);
    if (M2C_FIELD(&D_80083780, s16 *, 2) < temp_v1_3) {
        temp_v1_4 = M2C_FIELD(arg0, s16 *, 6);
        var_v0 = 5;
        if (M2C_FIELD(&D_80083780, s16 *, 6) >= temp_v1_4) {
            var_v0 = 3;
            if (temp_v1_4 >= M2C_FIELD(&D_80083780, s16 *, 6)) {
                return 4;
            }
        }
        /* Duplicate return node #13. Try simplifying control flow for better match */
        return var_v0;
    }
    if (temp_v1_3 < M2C_FIELD(&D_80083780, s16 *, 2)) {
        temp_v1_2 = M2C_FIELD(arg0, s16 *, 6);
        var_v0 = 7;
        if (M2C_FIELD(&D_80083780, s16 *, 6) >= temp_v1_2) {
            return temp_v1_2 < M2C_FIELD(&D_80083780, s16 *, 6);
        }
        /* Duplicate return node #13. Try simplifying control flow for better match */
        return var_v0;
    }
    temp_v1 = M2C_FIELD(arg0, s16 *, 6);
    if (M2C_FIELD(&D_80083780, s16 *, 6) >= temp_v1) {
        return (temp_v1 < M2C_FIELD(&D_80083780, s16 *, 6)) * 2;
    }
    var_v0 = 6;
    return var_v0;
}
