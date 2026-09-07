#include "common.h"
#include "m2c_compat.h"

s32 func_80019D44();         /* extern */
M2C_UNK *func_80019DFC(); /* extern */
extern M2C_UNK D_8001B234;
extern M2C_UNK D_8001C358;
extern M2C_UNK D_8001DE4A;

M2C_UNK *func_800162F8(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    M2C_UNK *var_s3;

    var_s3 = func_80019DFC(&D_8001B234, &D_8001C358, arg0, arg2);
    if (func_80019D44(&D_8001B234, arg0, arg2) != 0) {
        var_s3 = &D_8001DE4A;
    }
    return var_s3;
}
