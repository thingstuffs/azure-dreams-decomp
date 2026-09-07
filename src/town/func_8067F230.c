#include "common.h"

typedef s32 M2C_UNK;

s32 func_80017A54();
M2C_UNK *func_80017B0C();
extern M2C_UNK D_80018770;
extern M2C_UNK D_800188BC;
extern M2C_UNK D_8001A714;

M2C_UNK *func_8067F230(s32 arg0, s32 arg1, s32 arg2) {
    M2C_UNK *var_s2;

    var_s2 = func_80017B0C(&D_80018770, &D_800188BC, arg0, arg2);
    if (func_80017A54(&D_80018770, arg0, arg2) != 0) {
        if (arg2 == 0x26) {
            var_s2 = &D_8001A714;
        }
    }
    return var_s2;
}
