#include "common.h"
#include "m2c_compat.h"

M2C_UNK *func_80017BE8();                           /* extern */
extern M2C_UNK D_800170C8;
extern M2C_UNK D_8001BA8C;
extern M2C_UNK D_8001BA91;

M2C_UNK *func_80017C60(s32 arg2) {
    switch (arg2) {                                 /* irregular */
    case 1:
        return &D_800170C8;
    case 5:
        return &D_8001BA91;
    case 4:
        return &D_8001BA8C;
    default:
        return func_80017BE8();
    }
}
