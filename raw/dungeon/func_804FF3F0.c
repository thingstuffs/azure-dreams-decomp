#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80083160;

void func_80016BF0(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 temp_a3;
    s32 temp_v1;
    s32 temp_v1_3;
    s32 var_a1;
    s32 var_t1;
    u16 temp_a2;
    u8 *temp_v1_2;
    u8 *temp_v1_6;
    void *temp_a0;
    void *temp_t0;
    void *temp_v1_4;
    void *temp_v1_5;

    temp_t0 = &D_80083160 + 0x1DC;
    temp_v1 = M2C_FIELD(temp_t0, s32 *, 0x10);
    if (temp_v1 != 0) {
        var_t1 = 0;
        if ((arg3 << 0x10) > 0) {
            do {
                var_a1 = 0;
                if (arg2 > 0) {
                    temp_a3 = arg1 + var_t1;
                    do {
                        temp_a0 = M2C_FIELD(&D_80083160, s32 *, 0x1DC) + (((temp_a3 << M2C_FIELD(temp_t0, s16 *, 0x14)) + arg0 + var_a1) * 6);
                        temp_a2 = M2C_FIELD(temp_a0, u16 *, 0);
                        temp_v1_2 = temp_v1 + temp_a2;
                        if (*temp_v1_2 & 1) {
                            M2C_FIELD(temp_a0, u16 *, 4) = (u16) (M2C_FIELD(temp_a0, u16 *, 4) | 1);
                        }
                        if (*temp_v1_2 & 4) {
                            M2C_FIELD(temp_a0, u16 *, 4) = (u16) (M2C_FIELD(temp_a0, u16 *, 4) | 4);
                        }
                        if (*temp_v1_2 & 8) {
                            M2C_FIELD(temp_a0, u16 *, 4) = (u16) (M2C_FIELD(temp_a0, u16 *, 4) | 8);
                        }
                        if (*temp_v1_2 & 0x20) {
                            M2C_FIELD(temp_a0, u16 *, 4) = (u16) (M2C_FIELD(temp_a0, u16 *, 4) | 0x400);
                        }
                        temp_v1_3 = var_a1 + arg0;
                        if (*temp_v1_2 & 2) {
                            if (temp_v1_3 > 0) {
                                M2C_FIELD(temp_a0, u16 *, -2) = (u16) (M2C_FIELD(temp_a0, u16 *, -2) | 1);
                            }
                            if (temp_v1_3 < ((1 << M2C_FIELD(temp_t0, s16 *, 0x14)) - 1)) {
                                M2C_FIELD(temp_a0, u16 *, 0xA) = (u16) (M2C_FIELD(temp_a0, u16 *, 0xA) | 1);
                            }
                            if (temp_a3 > 0) {
                                temp_v1_4 = ((1 << M2C_FIELD(temp_t0, s16 *, 0x14)) * -6) + temp_a0;
                                M2C_FIELD(temp_v1_4, u16 *, 4) = (u16) (M2C_FIELD(temp_v1_4, u16 *, 4) | 1);
                            }
                            if (temp_a3 < ((1 << M2C_FIELD(temp_t0, s16 *, 0x16)) - 1)) {
                                temp_v1_5 = temp_a0 + (6 << M2C_FIELD(temp_t0, s16 *, 0x14));
                                M2C_FIELD(temp_v1_5, u16 *, 4) = (u16) (M2C_FIELD(temp_v1_5, u16 *, 4) | 1);
                            }
                        }
                        temp_v1_6 = temp_v1 + temp_a2;
                        if (*temp_v1_6 & 0x80) {
                            M2C_FIELD(temp_a0, u16 *, 4) = (u16) (M2C_FIELD(temp_a0, u16 *, 4) | 0x8000);
                        }
                        if (*temp_v1_6 & 0x40) {
                            M2C_FIELD(temp_a0, u16 *, 4) = (u16) (M2C_FIELD(temp_a0, u16 *, 4) | 0x40);
                        }
                        var_a1 += 1;
                    } while (var_a1 < arg2);
                }
                var_t1 += 1;
            } while (var_t1 < arg3);
        }
    }
}
