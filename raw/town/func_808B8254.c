#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80003544(M2C_UNK);                     /* extern */
M2C_UNK func_800036D8(s32, M2C_UNK);                /* extern */

s32 func_80003A54(void) {
    s32 temp_a0;
    s32 temp_s0;

    temp_a0 = *(s32 *)0x3F50;
    temp_s0 = M2C_FIELD((temp_a0 * 0x20), s32 *, 0x3FC4);
    func_800036D8(temp_a0, 2);
    func_80003544(2);
    return temp_s0 + *(s32 *)0x45F8;
}
