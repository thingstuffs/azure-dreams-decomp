#include "common.h"
#include "m2c_compat.h"

s32 func_800007E8(s32);                             /* extern */
M2C_UNK func_80000858(s32, M2C_UNK);                /* extern */
s32 func_80000A38();                                /* extern */
M2C_UNK func_80000BC8(u16);                         /* extern */
M2C_UNK func_80000C18(M2C_UNK);                     /* extern */
s32 func_80000C6C(u16);                             /* extern */

s32 func_800008A0(s32 arg0) {
    if ((func_80000C6C(*(u16 *)0xF12) == 0) && (func_80000C6C(0x278U) != 0)) {
        if (func_800007E8(arg0) != 0) {
            func_80000BC8(M2C_FIELD((arg0 * 4), u16 *, 0xF28));
            func_80000C18(0x278);
            return func_80000A38();
        }
        goto block_5;
    }
block_5:
    func_80000858(arg0, 0);
    return arg0;
}
