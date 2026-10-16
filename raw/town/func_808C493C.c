#include "common.h"
#include "m2c_compat.h"

s32 func_80000884(s32);                             /* extern */
M2C_UNK func_800008F4(s32, M2C_UNK);                /* extern */
s32 func_800009D4();                                /* extern */
M2C_UNK func_80000B40(u16);                         /* extern */
M2C_UNK func_80000B90(M2C_UNK);                     /* extern */
s32 func_80000BE4(u16);                             /* extern */

s32 func_8000093C(s32 arg0) {
    if ((func_80000BE4(*(u16 *)0xDA6) == 0) && (func_80000BE4(0x107U) != 0)) {
        if (func_80000884(arg0) != 0) {
            func_80000B40(M2C_FIELD((arg0 * 4), u16 *, 0xDB4));
            func_80000B90(0x107);
            return func_800009D4();
        }
        goto block_5;
    }
block_5:
    func_800008F4(arg0, 0);
    return arg0;
}
