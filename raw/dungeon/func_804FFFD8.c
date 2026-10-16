#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800E2970;
extern M2C_UNK D_800E2C40;

void func_800177D8(s16 arg0, s8 arg1, s8 arg2, s16 arg3) {
    s32 temp_a1;
    u16 temp_v0;
    void *temp_t0;
    void *temp_v0_2;

    temp_t0 = (arg0 * 0x14) + &D_800E2970;
    if (M2C_FIELD(temp_t0, s16 *, 0xA) != 0) {
        temp_a1 = arg0 << 6;
        temp_v0 = M2C_FIELD(temp_t0, u16 *, 0xE);
        M2C_FIELD(temp_t0, void **, 0x10) = (void *) (temp_a1 + &D_800E2C40);
        temp_v0_2 = ((s32) (temp_v0 << 0x10) >> 0xE) + temp_a1 + &D_800E2C40;
        M2C_FIELD(temp_t0, u16 *, 0xE) = (u16) (temp_v0 + 1);
        M2C_FIELD(temp_v0_2, s16 *, 2) = arg3;
        M2C_FIELD(temp_v0_2, s8 *, 0) = arg1;
        M2C_FIELD(temp_v0_2, s8 *, 1) = arg2;
    }
}
