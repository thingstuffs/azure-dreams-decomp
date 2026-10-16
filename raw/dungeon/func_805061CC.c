#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_8008333C;
extern M2C_UNK D_800E9FFA;

void func_8001D9CC(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4) {
    s16 *var_t0;
    s16 *var_t7;
    s16 temp_t3;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 var_t1;
    s16 var_t4;
    s32 temp_a0;
    s32 temp_t1;
    s32 temp_v1;
    void *temp_t6;
    void *temp_t7;
    void *temp_t7_2;
    void *temp_t7_3;
    void *temp_t7_4;
    void *var_a0;
    void *var_t0_2;
    void *var_t7_2;
    void *var_v1;

    temp_t1 = arg1 - 1;
    temp_t6 = &D_800E9FFA + 6;
    temp_t7 = (((temp_t1 << M2C_FIELD(&D_8008333C, s16 *, 0x14)) + arg0) * 6) + &D_800E9FFA;
    temp_t3 = arg4 + 0x40;
    M2C_FIELD(temp_t7, s16 *, 0) = 0xE;
    M2C_FIELD(temp_t7, s16 *, 2) = temp_t3;
    M2C_FIELD(temp_t7, s16 *, 4) = 9;
    temp_t7_2 = (((temp_t1 << M2C_FIELD(&D_8008333C, s16 *, 0x14)) + arg2) * 6) + temp_t6;
    M2C_FIELD(temp_t7_2, s16 *, 0) = 0xB;
    M2C_FIELD(temp_t7_2, s16 *, 2) = temp_t3;
    M2C_FIELD(temp_t7_2, s16 *, 4) = 9;
    temp_t7_3 = (((arg3 << M2C_FIELD(&D_8008333C, s16 *, 0x14)) + arg0) * 6) + &D_800E9FFA;
    M2C_FIELD(temp_t7_3, s16 *, 0) = 0xD;
    M2C_FIELD(temp_t7_3, s16 *, 2) = temp_t3;
    M2C_FIELD(temp_t7_3, s16 *, 4) = 9;
    temp_t7_4 = (((arg3 << M2C_FIELD(&D_8008333C, s16 *, 0x14)) + arg2) * 6) + temp_t6;
    M2C_FIELD(temp_t7_4, s16 *, 0) = 0xC;
    M2C_FIELD(temp_t7_4, s16 *, 2) = temp_t3;
    M2C_FIELD(temp_t7_4, s16 *, 4) = 9;
    var_t4 = arg0;
    var_t7 = (((temp_t1 << M2C_FIELD(&D_8008333C, s16 *, 0x14)) + arg0) * 6) + temp_t6;
    var_t0 = (((arg3 << M2C_FIELD(&D_8008333C, s16 *, 0x14)) + arg0) * 6) + temp_t6;
    if (arg0 < arg2) {
        var_a0 = var_t0 + 4;
        var_v1 = var_t7 + 4;
        do {
            temp_v0 = var_t4 + 1;
            var_t4 = temp_v0;
            *var_t7 = 0x12;
            *var_t0 = 0x10;
            M2C_FIELD(var_a0, s16 *, -2) = temp_t3;
            M2C_FIELD(var_v1, s16 *, -2) = temp_t3;
            M2C_FIELD(var_a0, s16 *, 0) = 9;
            M2C_FIELD(var_v1, s16 *, 0) = 9;
            var_v1 += 6;
            var_t7 += 6;
            var_a0 += 6;
            var_t0 += 6;
        } while (temp_v0 < arg2);
    }
    var_t1 = arg1;
    temp_a0 = var_t1 << M2C_FIELD(&D_8008333C, s16 *, 0x14);
    var_t7_2 = ((temp_a0 + arg0) * 6) + &D_800E9FFA;
    var_t0_2 = ((temp_a0 + arg2) * 6) + (&D_800E9FFA + 6);
    if (var_t1 < arg3) {
        do {
            temp_v0_2 = var_t1 + 1;
            var_t1 = temp_v0_2;
            M2C_FIELD(var_t7_2, s16 *, 0) = 0x11;
            M2C_FIELD(var_t0_2, s16 *, 0) = 0xF;
            M2C_FIELD(var_t0_2, s16 *, 2) = temp_t3;
            M2C_FIELD(var_t7_2, s16 *, 2) = temp_t3;
            M2C_FIELD(var_t0_2, s16 *, 4) = 9;
            M2C_FIELD(var_t7_2, s16 *, 4) = 9;
            temp_v1 = 6 << M2C_FIELD(&D_8008333C, s16 *, 0x14);
            var_t7_2 += temp_v1;
            var_t0_2 += temp_v1;
        } while (temp_v0_2 < arg3);
    }
}
