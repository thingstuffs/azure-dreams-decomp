#include "common.h"
#include "m2c_compat.h"

s32 func_80017BE0(s32);                             /* extern */
extern M2C_UNK D_800166F8;
extern M2C_UNK D_80016718;
extern s32 D_80019BB4;

s32 func_80017BE8(s32 arg2) {
    M2C_UNK *var_v1;

    if (arg2 == 1) {
        return func_80017BE0(D_80019BB4);
    }
    if (*(s32 *)0x80016738 != 0) {
        var_v1 = &D_80016718;
    } else {
        *(s32 *)0x80016738 = 1;
        var_v1 = &D_800166F8;
    }
    return *((D_80019BB4 * 4) + var_v1);
}
