#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80000BC8(u16);                         /* extern */
M2C_UNK func_80000C18(u16);                         /* extern */
s32 func_80000C6C(u16);                             /* extern */

void func_80000754(s32 arg0) {
    s32 var_v0;

    if (func_80000C6C(M2C_FIELD((arg0 * 4), u16 *, 0xF10)) != 0) {
        func_80000BC8(M2C_FIELD((arg0 * 4), u16 *, 0xF12));
        var_v0 = arg0 * 4;
    } else {
        func_80000C18(M2C_FIELD((arg0 * 4), u16 *, 0xF12));
        var_v0 = arg0 * 4;
    }
    func_80000BC8(M2C_FIELD(var_v0, u16 *, 0xF10));
}
