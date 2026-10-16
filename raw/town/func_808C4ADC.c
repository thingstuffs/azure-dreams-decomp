#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80000760(M2C_UNK);                     /* extern */
M2C_UNK func_800007F0(M2C_UNK);                     /* extern */
M2C_UNK func_800008F4(s32, M2C_UNK);                /* extern */

s32 func_80000ADC(void) {
    s32 temp_a0;
    s32 temp_s0;

    func_800007F0(1);
    temp_a0 = *(s32 *)0xD9C;
    temp_s0 = M2C_FIELD((temp_a0 * 0x10), s32 *, 0xDC8);
    func_800008F4(temp_a0, 1);
    func_80000760(1);
    return temp_s0 + *(s32 *)0xE50;
}
