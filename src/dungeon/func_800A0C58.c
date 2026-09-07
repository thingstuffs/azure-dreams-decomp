#include "common.h"
#include "m2c_compat.h"

s32 func_800990FC();                                /* extern */
s32 func_80099194();                  /* extern */
M2C_UNK func_80099290();                         /* extern */
s32 func_80099368();                    /* extern */
s32 func_80099734();                        /* extern */
s32 func_800999B0();                             /* extern */
M2C_UNK func_800A5720();                         /* extern */
M2C_UNK func_800A6424();                   /* extern */
extern M2C_UNK D_80089000[];
extern M2C_UNK D_800E0A03[];
extern M2C_UNK D_800E0A12[];

void func_800A63B8(s32 arg0, M2C_UNK arg1, s16 arg2) {
    register s32 temp_s2 ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

    temp_s2 = func_800990FC();
    if (arg2 == 0x15) {
        func_80099368(arg1, temp_s2);
        func_800A6424(&D_800E0A03);
        return;
    }
    func_80099290(func_800999B0(func_80099194(&D_80089000, func_80099734(arg0, func_80099194(&D_800E0A12, func_80099368(arg1, temp_s2))))));
    func_800A5720(temp_s2);
}
