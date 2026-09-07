#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_80065610();
extern s32 func_80066460();
extern void func_8006658C();
extern void func_800666F4();
extern void func_80067F20();

void *func_800A41D8(void *arg0, void *arg1, void *arg2_in, void *arg3, u16 arg4) {
    s32 sp30[2];
    u16 sp38;
    u16 sp40;
    u16 temp_bound;
    s16 temp_a1;
    register s32 var_a0_3 ASM_REG("$4");
    s16 var_v1_3;
    register s32 temp_a0_2 ASM_REG("$4");
    register s32 var_copy;
    s32 temp_a0_4;
    s32 temp_a0_5;
    register s32 temp_a1_2 ASM_REG("$5");
    register s32 temp_a2 ASM_REG("$6");
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 var_a0_2;
    s32 var_a0_4;
    s32 var_a1;
    s32 var_v1;
    u16 temp_v0;
    u16 tv14;
    s32 tmp7;
    u16 tv10;
    register s32 temp_dec ASM_REG("$3");
    u16 tsum;
    u16 temp_v0_2;
    u16 temp_v1;
    u32 temp_hi;
    void *temp_a0;
    void *temp_a1_3;
    void *temp_v0_7;
    void *var_a0;
    void *var_v0;
    register void *var_s0 ASM_REG("$16");
    register void *state ASM_REG("$17");
    register void *var_s2 ASM_REG("$18");
    register void *var_s3 ASM_REG("$19");
    register s32 var_s4 ASM_REG("$20");
    s32 var_s5;
    register s32 var_s6 ASM_REG("$22");
    s32 *var_s7;
    s32 *temp_dst;
    s32 temp_res;
    s32 var_fp;

    state = arg2_in;
    var_s3 = arg3;
    var_fp = 0;
    var_s6 = 0;
    sp38 = arg4;
    var_s7 = sp30;
    ASM_KEEP(state);
    ASM_KEEP(var_s3);
    ASM_KEEP(var_s6);
    ASM_KEEP(var_s7);
    ASM_KEEP(var_fp);
    temp_v0 = M2C_FIELD(arg0, u16 *, 8);
    temp_v1 = temp_v0 - 0x6200;
    temp_v0_2 = temp_v0 - 0x5400;
    sp40 = M2C_FIELD(arg0, u16 *, 0x16);
    M2C_FIELD(state, u16 *, 0x7C) = temp_v1;
    M2C_FIELD(state, u16 *, 0x74) = temp_v1;
    M2C_FIELD(state, u16 *, 0x8C) = temp_v0_2;
    M2C_FIELD(state, u16 *, 0x84) = temp_v0_2;
    do {
        M2C_FIELD(state, u16 *, 0x74) = (u16) (M2C_FIELD(state, u16 *, 0x74) + 0xE00);
        M2C_FIELD(state, u16 *, 0x7C) = (u16) (M2C_FIELD(state, u16 *, 0x7C) + 0xE00);
        M2C_FIELD(state, u16 *, 0x84) = (u16) (M2C_FIELD(state, u16 *, 0x84) + 0xE00);
        M2C_FIELD(state, u16 *, 0x8C) = (u16) (M2C_FIELD(state, u16 *, 0x8C) + 0xE00);
        if (func_80065610(state + 0x70, state + 0x78, state + 0x80, state + 0x88, state + 0xF0, state + 0xF4, state + 0xF8, state + 0xFC, state + 0x90, state + 0xC0, state + 0x94) > 0) {
            var_a1 = 0;
            if ((u32) ((M2C_FIELD(state, u16 *, 0xF0) + 0x20) & 0xFFFF) < 0x181U) {
                temp_bound = M2C_FIELD(state, u16 *, 0xF2) + 0x20;
                var_a1 = temp_bound < 0x121U;
            }
            var_v1 = 0;
            if ((u32) ((M2C_FIELD(state, u16 *, 0xF4) + 0x20) & 0xFFFF) < 0x181U) {
                temp_bound = M2C_FIELD(state, u16 *, 0xF6) + 0x20;
                var_v1 = temp_bound < 0x121U;
            }
            var_a0_2 = 0;
            var_a1 |= var_v1;
            if ((u32) ((M2C_FIELD(state, u16 *, 0xF8) + 0x20) & 0xFFFF) < 0x181U) {
                temp_bound = M2C_FIELD(state, u16 *, 0xFA) + 0x20;
                var_a0_2 = temp_bound < 0x121U;
            }
            var_v1 = 0;
            var_a0_4 = var_a1 | var_a0_2;
            if ((u32) ((M2C_FIELD(state, u16 *, 0xFC) + 0x20) & 0xFFFF) < 0x181U) {
                temp_bound = M2C_FIELD(state, u16 *, 0xFE) + 0x20;
                var_v1 = temp_bound < 0x121U;
            }
            if ((var_a0_4 | var_v1) != 0) {
                temp_a0 = var_s3 + 0x28;
                M2C_FIELD(var_s3, s32 *, 8) = M2C_FIELD(state, s32 *, 0xF0);
                M2C_FIELD(var_s3, s32 *, 0x18) = M2C_FIELD(state, s32 *, 0xF8);
                M2C_FIELD(var_s3, s32 *, 0x38) = M2C_FIELD(state, s32 *, 0xF4);
                M2C_FIELD(var_s3, s32 *, 0x48) = M2C_FIELD(state, s32 *, 0xFC);
                temp_v0_3 = (s32) ((s16) M2C_FIELD(state, u16 *, 0xF0) + (s16) M2C_FIELD(state, u16 *, 0xF4)) >> 1;
                M2C_FIELD(temp_a0, s16 *, 8) = (s16) temp_v0_3;
                M2C_FIELD(var_s3, s16 *, 0x10) = (s16) temp_v0_3;
                temp_v0_4 = (s32) ((s16) M2C_FIELD(state, u16 *, 0xF8) + (s16) M2C_FIELD(state, u16 *, 0xFC)) >> 1;
                M2C_FIELD(temp_a0, s16 *, 0x18) = (s16) temp_v0_4;
                M2C_FIELD(var_s3, s16 *, 0x20) = (s16) temp_v0_4;
                temp_v0_5 = (s32) ((s16) M2C_FIELD(state, u16 *, 0xF2) + (s16) M2C_FIELD(state, u16 *, 0xF6)) >> 1;
                M2C_FIELD(temp_a0, s16 *, 0xA) = (s16) temp_v0_5;
                M2C_FIELD(var_s3, s16 *, 0x12) = (s16) temp_v0_5;
                temp_v0_6 = (s32) ((s16) M2C_FIELD(state, u16 *, 0xFA) + (s16) M2C_FIELD(state, u16 *, 0xFE)) >> 1;
                M2C_FIELD(temp_a0, s16 *, 0x1A) = (s16) temp_v0_6;
                M2C_FIELD(var_s3, s16 *, 0x22) = (s16) temp_v0_6;
                var_a0_3 = (s16) M2C_FIELD(state, u16 *, 0x74) % 3584;
                M2C_FIELD(state, s32 *, 0x90) = (s32) var_a0_3;
                if (var_a0_3 < 0) {
                    var_a0_3 += 0xFF;
                }
                temp_v0_3 = var_a0_3 >> 8;
                M2C_FIELD(state, s32 *, 0x90) = temp_v0_3;
                temp_a1 = (sp40 + (var_s6 * 0xE)) - 0x40;
                var_v1_3 = 0x80;
                if (temp_a1 < 0x81) {
                    var_v1_3 = temp_a1;
                    if (temp_a1 < 0) {
                        var_v1_3 = 0;
                    }
                }
                var_s4 = 0;
                var_s0 = var_s3 + 0x25;
                temp_v0_7 = var_s3 + 0x28;
                M2C_FIELD(var_s3, s8 *, 6) = (s8) var_v1_3;
                M2C_FIELD(temp_v0_7, s8 *, 6) = (s8) var_v1_3;
                M2C_FIELD(var_s3, s8 *, 5) = (s8) var_v1_3;
                M2C_FIELD(temp_v0_7, s8 *, 5) = (s8) var_v1_3;
                M2C_FIELD(var_s3, s8 *, 4) = (s8) var_v1_3;
                M2C_FIELD(var_s3, s8 *, 0x2C) = (s8) var_v1_3;
                var_s5 = M2C_FIELD(state, s32 *, 0x118) + ((((var_s6 & 1) * 2) + ((s32) (sp38 << 0x10) >> 0xE)) * 0xC);
                var_s2 = var_s5 + 4;
                ASM_KEEP(var_s0);
                ASM_KEEP(var_s2);
                ASM_KEEP(var_s4);
                ASM_KEEP(var_s5);
                do {
                    func_800666F4(var_s3);
                    M2C_FIELD(var_s0, u8 *, -0x1E) = (u8) (M2C_FIELD(var_s0, u8 *, -0x1E) | (M2C_FIELD(arg1, u8 *, 0xF) & 2));
                    M2C_FIELD(state, s32 *, 8) = (s32) M2C_FIELD(var_s2, u8 *, 4);
                    M2C_FIELD(state, s32 *, 0xC) = (s32) M2C_FIELD(var_s2, u8 *, 5);
                    temp_a1_2 = M2C_FIELD(state, volatile s32 *, 8);
                    temp_a0_2 = M2C_FIELD(state, volatile s32 *, 0xC);
                    M2C_FIELD(state, s32 *, 0x10) = (s32) M2C_FIELD(var_s2, u8 *, 6);
                    var_copy = temp_a0_2;
                    M2C_FIELD(state, s32 *, 0x14) = (s32) M2C_FIELD(var_s2, u8 *, 7);
                    temp_a0_2 <<= 8;
                    M2C_FIELD(state, s32 *, 0xC) = temp_a0_2;
                    temp_a2 = M2C_FIELD(state, volatile s32 *, 0x14);
                    var_copy += temp_a2;
                    var_copy <<= 8;
                    M2C_FIELD(state, s32 *, 0x14) = var_copy;
                    M2C_FIELD(state, s32 *, 0x10) = (s32) (M2C_FIELD(state, s32 *, 0x10) + temp_a1_2);
                    var_copy = temp_a1_2;
                    ASM_KEEP_NV(var_copy);
                    M2C_FIELD(var_s0, s32 *, -0x19) = (s32) ((temp_a0_2 + var_copy) | (M2C_FIELD(var_s2, u16 *, 2) << 0x10));
                    M2C_FIELD(var_s0, s32 *, -0x11) = (s32) ((M2C_FIELD(state, s32 *, 0xC) + M2C_FIELD(state, s32 *, 0x10)) | (M2C_FIELD(var_s2, s16 *, 0) << 0x10));
                    M2C_FIELD(var_s0, s16 *, -9) = (s16) ((u16) M2C_FIELD(state, s32 *, 0x14) + (u16) M2C_FIELD(state, s32 *, 8));
                    temp_dec = M2C_FIELD(var_s0, u8 *, -0x11);
                    tv14 = (u16) M2C_FIELD(state, s32 *, 0x14);
                    tv10 = (u16) M2C_FIELD(state, s32 *, 0x10);
                    tsum = tv14 + tv10;
                    do {
                        temp_dec -= 1;
                    } while (0);
                    M2C_FIELD(var_s0, s16 *, -1) = (s16) tsum;
                    do {
                        M2C_FIELD(var_s0, u8 *, -0x11) = (u8) temp_dec;
                    } while (0);
                    M2C_FIELD(var_s0, u8 *, -1) = (u8) (M2C_FIELD(var_s0, u8 *, -1) - 1);
                    M2C_FIELD(var_s0, u8 *, -8) = (u8) (M2C_FIELD(var_s0, u8 *, -8) - 1);
                    M2C_FIELD(var_s0, u8 *, 0) = (u8) (M2C_FIELD(var_s0, u8 *, 0) - 1);
                    func_8006658C(M2C_FIELD(state, s32 *, 0x20) + (((u32) ((s32) (0 - ((var_s5 - M2C_FIELD(state, s32 *, 0x118)) * 0x55555555)) >> 2) / 12U) * 4), var_s3);
                    temp_hi = (u32) ((s32) (0 - ((var_s5 - M2C_FIELD(state, s32 *, 0x118)) * 0x55555555)) >> 2) / 12U;
                    var_s2 += 0xC;
                    var_s0 += 0x28;
                    var_s3 += 0x28;
                    temp_a0_4 = var_s4 * 4;
                    var_s4 += 1;
                    temp_dst = (s32 *)(temp_a0_4 + (s32) var_s7);
                    var_s5 += 0xC;
                    temp_res = M2C_FIELD(state, s32 *, 0x20);
                    temp_res += temp_hi * 4;
                    *temp_dst = temp_res;
                } while (var_s4 < 2);
                var_s0 = var_s3;
                var_s4 = 0;
                var_s2 = var_s7;
                do {
                    func_80067F20(var_s0, 1, 0, func_80066460(0, 0, 0x140, 0) & 0xFFFF, 0);
                    temp_a1_3 = var_s0;
                    var_s0 += 0xC;
                    temp_a0_5 = *(s32 *)var_s2;
                    var_s2 += 4;
                    var_s4 += 1;
                    func_8006658C(temp_a0_5, temp_a1_3);
                } while (var_s4 < 2);
                var_s3 = var_s0;
                var_fp += 1;
            }
        }
        var_s6 += 1;
    } while (var_s6 < 0xE);
    var_v0 = 0;
    if (var_fp != 0) {
        var_v0 = var_s3;
    }
    return var_v0;
}
