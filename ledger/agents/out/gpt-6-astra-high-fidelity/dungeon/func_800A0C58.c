#include "common.h"
#include "m2c_compat.h"

s32 func_800990FC(s32, M2C_UNK, s32, s32);                                /* extern */
s32 func_80099194();                  /* extern */
M2C_UNK func_80099290();                         /* extern */
s32 func_80099368();                    /* extern */
s32 func_80099734();                        /* extern */
s32 func_800999B0();                             /* extern */
M2C_UNK func_800A5720();                         /* extern */
extern M2C_UNK D_80089000[];
extern M2C_UNK D_800E0A03[];
extern M2C_UNK D_800E0A12[];

void func_800A63B8(s32 arg0, M2C_UNK arg1, s32 arg2, s32 arg3) {
    register s32 temp_s2 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    s32 temp_v0;

    temp_s2 = func_800990FC(arg0, arg1, arg2, arg3);
    if ((s16)arg2 == 0x15) {
        temp_v0 = func_80099194(D_800E0A03, func_80099368(arg1, temp_s2));
    } else {
        temp_v0 = func_80099194(D_800E0A12, func_80099368(arg1, temp_s2));
    }
    func_80099290(func_800999B0(func_80099194(&D_80089000, func_80099734(arg0, temp_v0))));
    func_800A5720(temp_s2);
}
