#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001D9CC(s16, s16, s16, s16, s32);     /* extern */
M2C_UNK func_8001DD08(void *, s16);                 /* extern */
M2C_UNK func_8001DD48(void *, s16);                 /* extern */
s32 func_800A6D30(s32, s16, s16, s32);              /* extern */
extern s16 D_8008146E;
extern M2C_UNK D_8008333C;
extern M2C_UNK D_800EA000;

void func_8001D5D8(void *arg0, s16 arg2, s32 arg3) {
    u16 sp18;
    u16 sp20;
    s16 sp28;
    u16 sp30;
    s32 sp38;
    u16 sp40;
    u16 sp48;
    u16 sp50;
    s32 sp58;
    s32 sp5C;
    s32 sp60;
    s32 sp64;
    s32 sp68;
    s16 temp_s0_2;
    s16 temp_s1_2;
    s16 temp_t0;
    s16 var_a1;
    s16 var_a1_2;
    s16 var_a2;
    s16 var_s1;
    s16 var_s5_2;
    s32 temp_s1_3;
    s32 temp_t5_3;
    s32 temp_v0;
    s32 var_a0_2;
    s32 var_a3;
    s32 var_s6;
    s32 var_v0_2;
    s32 var_v1;
    u16 temp_a0;
    u16 temp_fp;
    u16 temp_s0;
    u16 temp_s1;
    u16 temp_t5;
    u16 temp_t5_2;
    u16 temp_v1;
    u16 var_s0;
    u16 var_s4;
    u16 var_s5;
    u16 var_v0;
    u16 var_v0_3;
    void *temp_v1_2;
    void *temp_v1_3;
    void *var_a0;

    var_a0 = arg0;
    var_a2 = arg2;
    var_a3 = arg3;
    temp_fp = M2C_FIELD(var_a0, u16 *, 8);
    temp_t5 = M2C_FIELD(var_a0, u16 *, 2);
    temp_t0 = temp_fp - 0x80;
    var_s5 = temp_t5;
    sp20 = temp_t5;
    temp_t5_2 = M2C_FIELD(var_a0, u16 *, 0);
    sp18 = temp_t5_2;
    temp_s0 = M2C_FIELD(var_a0, u16 *, 4);
    temp_s1 = M2C_FIELD(var_a0, u16 *, 6);
    var_a1 = temp_t5_2 + temp_s0;
    temp_v1 = var_s5 + temp_s1;
    sp30 = temp_v1;
    sp28 = var_a1;
    if ((var_s5 << 0x10) < (temp_v1 << 0x10)) {
        var_a3 = var_a1 << 0x10;
        do {
            var_s4 = sp18;
            var_v0 = var_s5 + 1;
            if ((temp_t5_2 << 0x10) < var_a3) {
                var_a2 = (s16) var_s5;
                var_a1 = var_a1;
                do {
                    temp_v0 = var_s4 << 0x10;
                    temp_a0 = var_s4 + 1;
                    var_s4 = temp_a0;
                    var_a0 = (void *) ((s16) temp_a0 < var_a1);
                    temp_v1_2 = (((var_a2 << M2C_FIELD(&D_8008333C, s16 *, 0x14)) + (temp_v0 >> 0x10)) * 6) + &D_800EA000;
                    M2C_FIELD(temp_v1_2, s16 *, 0) = 0x19;
                    M2C_FIELD(temp_v1_2, s16 *, 2) = temp_t0;
                    M2C_FIELD(temp_v1_2, s16 *, 4) = 6;
                } while (var_a0 != NULL);
                var_v0 = var_s5 + 1;
            }
            var_s5 = var_v0;
        } while ((var_v0 << 0x10) < (sp30 << 0x10));
    }
    sp48 = func_800A6D30((s32) var_a0, var_a1, var_a2, var_a3) & 1;
    var_v1 = (s16) temp_s0 + (s16) temp_s1;
    if (var_v1 < 0) {
        var_v1 += 3;
    }
    var_a0_2 = var_v1 >> 2;
    if (D_8008146E < 5) {
        var_a0_2 = var_v1 >> 4;
    }
    sp38 = var_a0_2;
    if (var_a0_2 > 0) {
        sp58 = (s32) (s16) temp_s0;
        sp5C = (s32) (s16) temp_s1;
        sp60 = (s32) (s16) sp30;
        sp68 = (u16) sp28 << 0x10;
        do {
            temp_s0_2 = sp18 + ((s32) (func_800A6D30() & 0xFFFF) % sp58);
            temp_s1_2 = sp20 + ((s32) (func_800A6D30() & 0xFFFF) % sp5C);
            var_s5_2 = temp_s1_2;
            sp40 = (((s32) (sp58 - (temp_s0_2 - (s16) sp18)) / 2) + (func_800A6D30() & 7)) - 4;
            temp_s1_3 = (((s32) (sp5C - (temp_s1_2 - (s16) sp20)) / 2) + (func_800A6D30() & 7)) - 4;
            var_s6 = temp_s1_3;
            sp50 = (func_800A6D30() & 7) != 0;
            if ((temp_s1_3 << 0x10) > 0) {
                sp64 = sp68 >> 0x10;
                do {
                    var_v0_2 = var_s6 - 1;
                    if (var_s5_2 < sp60) {
                        var_s0 = sp40;
                        var_s1 = temp_s0_2;
                        if ((var_s0 << 0x10) > 0) {
                            do {
                                if (var_s1 < sp64) {
                                    temp_v1_3 = (((var_s5_2 << M2C_FIELD(&D_8008333C, s16 *, 0x14)) + var_s1) * 6) + &D_800EA000;
                                    if (sp48 != 0) {
                                        if (sp50 == 0) {
                                            var_a1_2 = temp_fp - 0xC0;
                                            goto block_24;
                                        }
                                        goto block_25;
                                    }
                                    if (sp50 != 0) {
                                        var_a1_2 = temp_fp - 0xC0;
block_24:
                                        func_8001DD48(temp_v1_3, var_a1_2);
                                        var_v0_3 = var_s0 - 1;
                                    } else {
block_25:
                                        func_8001DD08(temp_v1_3, (s16) (temp_fp - 0x40));
                                        goto block_26;
                                    }
                                } else {
block_26:
                                    var_v0_3 = var_s0 - 1;
                                }
                                var_s0 = var_v0_3;
                                var_s1 += 1;
                            } while ((var_v0_3 << 0x10) > 0);
                        }
                        var_v0_2 = var_s6 - 1;
                    }
                    var_s6 = var_v0_2;
                    var_s5_2 += 1;
                } while ((var_v0_2 << 0x10) > 0);
            }
            temp_t5_3 = sp38 - 1;
            sp38 = temp_t5_3;
        } while (temp_t5_3 > 0);
    }
    func_8001D9CC((s16) sp18, (s16) sp20, (s16) (u16) sp28, (s16) sp30, (s32) (s16) temp_fp);
}
