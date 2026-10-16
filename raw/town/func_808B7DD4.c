#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80003BCC(u16);                         /* extern */
M2C_UNK func_80003C1C(u16);                         /* extern */
s32 func_80003C70(u16);                             /* extern */

void func_800035D4(s32 arg0) {
    s32 var_v0;

    if (func_80003C70(M2C_FIELD((arg0 * 4), u16 *, 0x3F58)) != 0) {
        func_80003BCC(M2C_FIELD((arg0 * 4), u16 *, 0x3F5A));
        var_v0 = arg0 * 4;
    } else {
        func_80003C1C(M2C_FIELD((arg0 * 4), u16 *, 0x3F5A));
        var_v0 = arg0 * 4;
    }
    func_80003BCC(M2C_FIELD(var_v0, u16 *, 0x3F58));
}
