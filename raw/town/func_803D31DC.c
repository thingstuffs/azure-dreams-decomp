#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80018878(M2C_UNK *, s32);              /* extern */
M2C_UNK func_800188B4(M2C_UNK *, M2C_UNK *);        /* extern */
extern M2C_UNK D_80016124;
extern M2C_UNK D_8001B330;

M2C_UNK *func_8001A1DC(s32 arg0) {
    func_80018878(&D_8001B330, arg0);
    func_800188B4(&D_8001B330, &D_80016124);
    return &D_8001B330;
}
