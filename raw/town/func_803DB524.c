#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80016774;
extern M2C_UNK D_80016794;
extern s32 D_80019BB4;
extern M2C_UNK D_8001BA8C;
extern M2C_UNK D_8001BA91;

M2C_UNK *func_80017D24(s32 arg2) {
    M2C_UNK *var_v1;

    switch (arg2) {                                 /* irregular */
    case 5:
        return &D_8001BA91;
    case 4:
        return &D_8001BA8C;
    default:
        var_v1 = &D_80016774;
block_7:
        return *((D_80019BB4 * 4) + var_v1);
    case 1:
        var_v1 = &D_80016794;
        goto block_7;
    }
}
