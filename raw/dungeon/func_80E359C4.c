#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_800478B8(void *, s32, void *);         /* extern */

void func_801511C4(void *arg0, void *arg1, void *arg2) {
    s32 temp_a1;
    s32 var_a1;
    s32 var_v0;
    s32 var_v0_2;
    u16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, u16 *, 0) + 1;
    M2C_FIELD(arg0, u16 *, 0) = temp_v0;
    if ((s16) temp_v0 >= 8) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
        return;
    }
    if ((s16) temp_v0 >= 6) {
        var_a1 = M2C_FIELD(arg0, s16 *, 4) + ((s16) temp_v0 + 6);
        var_v0 = var_a1;
        if (var_a1 < 0) {
            var_v0 = var_a1 + 7;
        }
        M2C_FIELD(arg2, s16 *, 0x12) = (s16) (M2C_FIELD(arg0, u16 *, 6) + (var_a1 - ((var_v0 >> 3) * 8)) + 8);
    } else {
        temp_a1 = M2C_FIELD(arg0, s16 *, 4) + ((s16) temp_v0 + 6);
        var_v0_2 = temp_a1;
        if (temp_a1 < 0) {
            var_v0_2 = temp_a1 + 7;
        }
        M2C_FIELD(arg2, s16 *, 0x12) = (s16) (M2C_FIELD(arg0, u16 *, 6) + (temp_a1 - ((var_v0_2 >> 3) * 8)));
        var_a1 = M2C_FIELD(arg1, s32 *, 0x10);
        M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
        M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + var_a1);
    }
    func_800478B8(arg2, var_a1, arg1);
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
        func_80047784(arg2, 0x30, 0);
    }
}
