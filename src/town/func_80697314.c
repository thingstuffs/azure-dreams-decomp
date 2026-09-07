#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800179A0();                            /* extern */
s32 func_80017B24();         /* extern */
M2C_UNK *func_80017BDC(); /* extern */
s32 func_80018820();                                /* extern */
extern M2C_UNK D_8001896C;
extern M2C_UNK D_80018AD0;
extern M2C_UNK D_80019C79;

M2C_UNK *func_80697314(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    M2C_UNK *var_s1;

    if (func_80018820() >= 0x1E) {
        func_800179A0();
    }
    var_s1 = func_80017BDC(&D_8001896C, &D_80018AD0, arg0, arg2);
    if (func_80017B24(&D_8001896C, arg0, arg2) != 0) {
        var_s1 = &D_80019C79;
    }
    return var_s1;
}
