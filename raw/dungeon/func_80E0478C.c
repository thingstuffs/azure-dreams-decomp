#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800478B8(void *);                      /* extern */

void func_80155F8C(void *arg0, void *arg1, void *arg2) {
    u16 temp_v0;
    u32 temp_v0_2;
    u32 temp_v1;

    func_800478B8(arg2);
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
        return;
    }
    temp_v0 = M2C_FIELD(arg2, u16 *, 0x1E) + 0x200;
    M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0;
    M2C_FIELD(arg2, u16 *, 0x1C) = temp_v0;
    temp_v0_2 = M2C_FIELD(arg1, u32 *, 0xC);
    temp_v1 = M2C_FIELD(arg1, u32 *, 0x10);
    M2C_FIELD(arg1, u32 *, 0xC) = (u32) ((s32) (temp_v0_2 + (temp_v0_2 >> 0x1F)) >> 1);
    M2C_FIELD(arg1, u32 *, 0x10) = (u32) ((s32) (temp_v1 + (temp_v1 >> 0x1F)) >> 1);
    M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) - 0x4E20);
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, u32 *, 0xC));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, u32 *, 0x10));
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
}
