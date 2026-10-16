#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800007F0(M2C_UNK);                     /* extern */
s32 func_800009D4();                                /* extern */
M2C_UNK func_80000A30();                            /* extern */
M2C_UNK func_80000CB0(s32, s32);                    /* extern */

s32 func_80000A88(void) {
    s32 temp_v0;

    func_800007F0(0);
    func_80000A30();
    temp_v0 = func_800009D4();
    *(s32 *)0xD9C = temp_v0;
    func_80000CB0(temp_v0, *(s32 *)0xDA0);
    return *(void *)0xD9C;
}
