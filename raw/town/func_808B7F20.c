#include "common.h"
#include "m2c_compat.h"

s32 func_80003668(s32);                             /* extern */
M2C_UNK func_800036D8(s32, M2C_UNK);                /* extern */
s32 func_800037B8();                                /* extern */
M2C_UNK func_80003BCC(u16);                         /* extern */
M2C_UNK func_80003C1C(M2C_UNK);                     /* extern */
s32 func_80003C70(u16);                             /* extern */

s32 func_80003720(s32 arg0) {
    if ((func_80003C70(*(u16 *)0x3F5A) == 0) && (func_80003C70(0x1F9U) != 0)) {
        if (func_80003668(arg0) != 0) {
            func_80003BCC(M2C_FIELD((arg0 * 4), u16 *, 0x3F88));
            func_80003C1C(0x1F9);
            return func_800037B8();
        }
        goto block_5;
    }
block_5:
    func_800036D8(arg0, 0);
    return arg0;
}
