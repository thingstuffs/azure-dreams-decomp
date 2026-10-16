#include "common.h"
#include "m2c_compat.h"

s32 func_80019D44(M2C_UNK *, s32, M2C_UNK);         /* extern */
M2C_UNK *func_80019DFC(M2C_UNK *, M2C_UNK *, s32, M2C_UNK); /* extern */
extern M2C_UNK D_8001BB84;
extern M2C_UNK D_8001C358;
extern M2C_UNK D_8001E891;

M2C_UNK *func_8001789C(s32 arg0, M2C_UNK arg2) {
    M2C_UNK *temp_s0;

    temp_s0 = func_80019DFC(&D_8001BB84, &D_8001C358, arg0, arg2);
    if (func_80019D44(&D_8001BB84, arg0, arg2) == 0) {
        return temp_s0;
    }
    return &D_8001E891;
}
