#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80000B40(u16);                         /* extern */
M2C_UNK func_80000B90(u16);                         /* extern */
s32 func_80000BE4(u16);                             /* extern */

void func_800007F0(s32 arg0) {
    s32 var_v0;

    if (func_80000BE4(M2C_FIELD((arg0 * 4), u16 *, 0xDA4)) != 0) {
        func_80000B40(M2C_FIELD((arg0 * 4), u16 *, 0xDA6));
        var_v0 = arg0 * 4;
    } else {
        func_80000B90(M2C_FIELD((arg0 * 4), u16 *, 0xDA6));
        var_v0 = arg0 * 4;
    }
    func_80000B40(M2C_FIELD(var_v0, u16 *, 0xDA4));
}
