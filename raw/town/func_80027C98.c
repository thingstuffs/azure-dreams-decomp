#include "common.h"
#include "m2c_compat.h"

s32 func_800644B8(s32);                             /* extern */
M2C_UNK func_800C4174();                            /* extern */

void func_800C53F8(void *arg0, void *arg2) {
    s32 temp_v0_2;
    s32 var_v1;
    u16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, u16 *, 0x6C) - 1;
    M2C_FIELD(arg0, u16 *, 0x6C) = temp_v0;
    if ((s16) temp_v0 <= 0) {
        M2C_FIELD(arg2, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(arg2, s16 *, 0x1C) = 0x1000;
        func_800C4174();
        return;
    }
    temp_v0_2 = func_800644B8((s16) temp_v0 * 0x199);
    var_v1 = temp_v0_2 >> 2;
    if (temp_v0_2 < 0) {
        var_v1 = (s32) (temp_v0_2 + 3) >> 2;
    }
    M2C_FIELD(arg2, s16 *, 0x1C) = (s16) (0x1000 - var_v1);
    M2C_FIELD(arg2, s16 *, 0x1E) = (s16) ((func_800644B8((s16) M2C_FIELD(arg0, u16 *, 0x6C) * 0x199) / 4) + 0x1000);
}
