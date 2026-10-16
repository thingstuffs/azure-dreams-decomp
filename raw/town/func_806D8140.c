#include "common.h"
#include "m2c_compat.h"

s32 func_80017A54(M2C_UNK *, s32, M2C_UNK);         /* extern */
M2C_UNK *func_80017B0C(M2C_UNK *, M2C_UNK *, s32, s32); /* extern */
extern M2C_UNK D_80018A58;
extern M2C_UNK D_80019104;
extern M2C_UNK D_800197D0;
extern M2C_UNK D_8001AE04;

M2C_UNK *func_80016940(s32 arg0, s32 arg2) {
    M2C_UNK *temp_s3;

    temp_s3 = func_80017B0C(&D_80018A58, &D_80019104, arg0, arg2);
    switch (arg2) {                                 /* irregular */
    case 45:
        if (func_80017A54(&D_80018A58, arg0, 0x2D) != 0) {
            return &D_800197D0;
        }
        if ((arg2 == 0x2E) && (func_80017A54(&D_80018A58, arg0, 0x2E) != 0)) {
            return &D_8001AE04;
        }
    default:
        return temp_s3;
    }
}
