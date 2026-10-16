#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C4174();                            /* extern */
extern M2C_UNK D_80083498;

void func_800CE558(void *arg0, void *arg1) {
    u16 temp_v0;
    u32 temp_v0_2;
    u32 temp_v0_3;
    u32 temp_v0_4;

    temp_v0 = M2C_FIELD(arg0, u16 *, 0x6C) - 1;
    M2C_FIELD(arg0, u16 *, 0x6C) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg0, s16 *, 0x90) = 1;
        func_800C4174();
    }
    temp_v0_2 = M2C_FIELD(M2C_FIELD(&D_80083498, void **, 8), s16 *, 2) - M2C_FIELD(arg1, s16 *, 2);
    M2C_FIELD(arg1, s16 *, 2) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 2) + ((s32) (temp_v0_2 + (temp_v0_2 >> 0x1F)) >> 1));
    temp_v0_3 = M2C_FIELD(M2C_FIELD(&D_80083498, void **, 8), s16 *, 6) - (M2C_FIELD(arg1, s16 *, 6) - 0x10);
    M2C_FIELD(arg1, s16 *, 6) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 6) + ((s32) (temp_v0_3 + (temp_v0_3 >> 0x1F)) >> 1));
    temp_v0_4 = M2C_FIELD(M2C_FIELD(&D_80083498, void **, 8), s16 *, 0xA) - M2C_FIELD(arg1, s16 *, 0xA);
    M2C_FIELD(arg1, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 0xA) + ((s32) (temp_v0_4 + (temp_v0_4 >> 0x1F)) >> 1));
}
