#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800478B8(void *);                      /* extern */

void func_8016DEC0(void *arg0, void *arg1, void *arg2) {
    s16 temp_v1;
    s32 var_v0;
    u16 temp_v0;
    u16 temp_v0_2;

    var_v0 = M2C_FIELD(arg0, s16 *, 0xC) - M2C_FIELD(arg1, s16 *, 2);
    if (var_v0 < 0) {
        var_v0 += 3;
    }
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + ((var_v0 >> 2) << 0x10));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + (((s32) (M2C_FIELD(arg0, s16 *, 0xE) - M2C_FIELD(arg1, s16 *, 6)) / 4) << 0x10));
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + (((s32) (M2C_FIELD(arg0, s16 *, 0x10) - M2C_FIELD(arg1, s16 *, 0xA)) / 4) << 0x10));
    func_800478B8(arg2);
    temp_v1 = M2C_FIELD(arg0, s16 *, 0x4C);
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_v0 = M2C_FIELD(arg2, u16 *, 0x1E) - 0x80;
        M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0;
        M2C_FIELD(arg2, u16 *, 0x1C) = temp_v0;
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x48) - 1;
        M2C_FIELD(arg0, u16 *, 0x48) = temp_v0_2;
        if ((temp_v0_2 << 0x10) <= 0) {
            M2C_FIELD(arg0, s16 *, 0x4C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x4C) + 1);
            return;
        }
        return;
    case 1:
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
        break;
    }
}
