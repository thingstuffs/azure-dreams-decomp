#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_8008333C;
extern M2C_UNK D_800EA000;

void func_80017A9C(void) {
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a1;
    void *temp_v1;
    void *temp_v1_2;
    void *temp_v1_3;
    void *temp_v1_4;

    var_a0 = 0;
    if ((1 << M2C_FIELD(&D_8008333C, s16 *, 0x16)) > 0) {
        do {
            temp_v1 = ((var_a0 << M2C_FIELD(&D_8008333C, s16 *, 0x14)) * 6) + &D_800EA000;
            M2C_FIELD(temp_v1, s16 *, 0) = 3;
            M2C_FIELD(temp_v1, s16 *, 2) = 0x400;
            M2C_FIELD(temp_v1, u16 *, 4) = (u16) (M2C_FIELD(temp_v1, u16 *, 4) | 0x8001);
            temp_v1_2 = (((var_a0 + 1) << M2C_FIELD(&D_8008333C, s16 *, 0x14)) * 6) + (&D_800EA000 - 6);
            M2C_FIELD(temp_v1_2, s16 *, 0) = 3;
            M2C_FIELD(temp_v1_2, s16 *, 2) = 0x400;
            M2C_FIELD(temp_v1_2, u16 *, 4) = (u16) (M2C_FIELD(temp_v1_2, u16 *, 4) | 0x8001);
            var_a0 += 1;
        } while (var_a0 < (1 << M2C_FIELD(&D_8008333C, s16 *, 0x16)));
    }
    var_a0_2 = 0;
    if ((1 << M2C_FIELD(&D_8008333C, s16 *, 0x16)) > 0) {
        var_a1 = 0;
        do {
            temp_v1_3 = var_a1 + &D_800EA000;
            M2C_FIELD(temp_v1_3, s16 *, 0) = 3;
            M2C_FIELD(temp_v1_3, s16 *, 2) = 0x400;
            M2C_FIELD(temp_v1_3, u16 *, 4) = (u16) (M2C_FIELD(temp_v1_3, u16 *, 4) | 0x8001);
            temp_v1_4 = (((((1 << M2C_FIELD(&D_8008333C, s16 *, 0x16)) - 1) << M2C_FIELD(&D_8008333C, s16 *, 0x14)) + var_a0_2) * 6) + (&D_800EA000 - 6);
            M2C_FIELD(temp_v1_4, s16 *, 0) = 3;
            M2C_FIELD(temp_v1_4, s16 *, 2) = 0x400;
            M2C_FIELD(temp_v1_4, u16 *, 4) = (u16) (M2C_FIELD(temp_v1_4, u16 *, 4) | 0x8001);
            var_a0_2 += 1;
            var_a1 += 6;
        } while (var_a0_2 < (1 << M2C_FIELD(&D_8008333C, s16 *, 0x16)));
    }
}
