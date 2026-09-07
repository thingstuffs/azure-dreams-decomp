/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C6B40_0 {
    u8 pad_00[0x8];
    void * unk_08;
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_0C;   /* overlapping accesses */
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x2];
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u8 pad_1E[0x2];
    u16 unk_20;
} S_800C6B40_0;   /* arg2 in func_800C6B40 */

typedef struct S_800C6B40_1 {
    u8 unk_00;
    u8 pad_01[0x3];
    u16 unk_04;
    u16 unk_06;
    union { struct { u8 v; } at00; struct { void * v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; struct { u8 pad[0x3]; u8 v; } at03; } unk_08;   /* overlapping accesses */
} S_800C6B40_1;   /* var_s3 in func_800C6B40 */

typedef struct S_800C6B40_2_pre {
    s8 unk_00;
    u8 pad_01[0x3];
} S_800C6B40_2_pre;   /* the 0x4 bytes before var_s0 in func_800C6B40, addressed as var_s0[-1] */

typedef struct S_800C6B40_2 {
    s8 unk_00;
    u8 pad_01[0x4];
    s8 unk_05;
    s8 unk_06;
    u8 pad_07[0x6];
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x6];
    s8 unk_15;
    s8 unk_16;
    u8 pad_17[0x6];
    s8 unk_1D;
    s8 unk_1E;
} S_800C6B40_2;   /* var_s0 in func_800C6B40 */

M2C_UNK func_80064840();
M2C_UNK func_800649A0();
M2C_UNK func_80064A40();
M2C_UNK func_80064BC0();
M2C_UNK func_80064CF0();
M2C_UNK func_80064D80();
u32 func_80065420();
M2C_UNK func_800654B0();
M2C_UNK func_80065820();
M2C_UNK func_8006658C();
extern s32 D_8006CD30[];
extern u8 D_80083160[];

void func_800C6B40(s32 arg0, void *arg1, void *arg2, s16 arg3) {
    u8 *scratch = (u8 *)0x1F800000;
    u8 *state;
    u8 *dtail;
    s32 sp28;
    s32 temp_v0_10;
    s16 temp_v0_5;
    s16 temp_v0_6;
    s32 temp_v0_7;
    s16 temp_v0_8;
    s16 temp_v0_9;
    s32 (*temp_v0_16)(s32, void *, void *, void *, s32);
    s32 temp_a1;
    s32 temp_a1b;
    s32 temp_a1_2;
    s32 temp_v0_11;
    s32 temp_v0_12;
    s32 temp_v0_13;
    s32 temp_v0_14;
    s32 temp_v0_17;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a0_4;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a1_3;
    s32 var_a2;
    s32 var_a3;
    s32 var_fp;
    register s32 var_s2;
    s32 var_s4;
    s32 var_s5;
    s32 var_s6;
    s32 var_s7;
    s32 var_t0;
    s32 var_t1;
    register s32 var_t2;
    register s32 var_t3;
    register s32 var_t4;
    register s32 var_t5;
    register s32 var_t6;
    register s32 var_t8;
    s32 var_v0;
    s32 var_v1;
    s32 tmp_v0;
    s32 temp_last;
    s32 var_v1_2;
    s32 var_a0_5;
    s32 var_v1_3;
    u16 temp_a0;
    u16 inner_f0;
    u16 temp_v0_15;
    u32 temp_h12;
    u32 temp_d10a;
    u32 temp_d10b;
    u32 temp_u;
    u32 temp_d14a;
    u32 temp_d14b;
    u32 temp_h14;
    s32 temp_h18;
    register void *a0p ASM_REG("$4");   /* MATCH pin: retail delay-slot fill depends on it */
    u32 temp_v0_3;
    u32 temp_v0_4;
    u16 temp_v1;
    u16 temp_v1_2;
    u16 temp_v1_4;
    s8 var_v0_2;
    u32 temp_v0;
    u32 temp_v0_2;
    u32 var_t7;
    u8 temp_v1_3;
    register void *var_s0 ASM_REG("$16");   /* MATCH pin: keeps a constant in a register as retail does */
    void *var_s3;

    dtail = D_80083160;
    state = *(u8 **)D_80083160;
    *(u32 *)(scratch + 0x0EC) = NULL;
    *(u16 *)(scratch + 0x08C) = 0;
    *(u16 *)(scratch + 0x084) = 0;
    *(u16 *)(scratch + 0x07C) = 0;
    *(u16 *)(scratch + 0x074) = 0;
    *(u32 *)(scratch + 0x020) = state + 0xB0;
    *(u16 *)(scratch + 0x000) = (u16)(*(u16 *)((u8 *)arg1 + 2));
    *(u16 *)(scratch + 0x002) = (u16)(*(u16 *)((u8 *)arg1 + 6));
    *(u16 *)(scratch + 0x004) = (u16)(*(u16 *)((u8 *)arg1 + 0xA));
    sp28 = *(s32 *)(state + 0x8D0);
    *(u32 *)(scratch + 0x0C0) = func_80065420(scratch, scratch + 0xB8, scratch + 0x90, scratch + 0x94);
    var_s2 = (s32)D_8006CD30;
    (*(u16 *)((u8 *)arg2 + 0x14)) = (u16)((*(u16 *)((u8 *)arg2 + 0x14)) | 0x8000);
    temp_v0 = *(volatile u32 *)(scratch + 0x0C0);
    *(s32 *)((u8 *)var_s2 + 0x1C) = (s32)(temp_v0 * 4);
    temp_v0 -= 8;
    temp_v0_2 = temp_v0 - arg3;
    *(u32 *)(scratch + 0x0C0) = temp_v0_2;
    if (temp_v0_2 < 0x1E0U) {
        func_800649A0();
        *(u16 *)(scratch + 0x0B8) = (u16)(*(u16 *)(scratch + 0x0B8) - 0xA0);
        *(u16 *)(scratch + 0x0BA) = (u16)(*(u16 *)(scratch + 0x0BA) - 0x78);
        *(u32 *)(scratch + 0x030) = *(s16 *)(dtail + 0xC4);
        *(u32 *)(scratch + 0x034) = *(s16 *)(dtail + 0xC6);
        *(u32 *)(scratch + 0x038) = *(s16 *)(dtail + 0xC8);
        *(u16 *)(scratch + 0x100) = (u16)(*(u16 *)((u8 *)arg2 + 0x16));
        *(u16 *)(scratch + 0x104) = (s16)(((S_800C6B40_0 *)arg2)->unk_1A - (u16)*(u32 *)(scratch + 0x034));
        *(u16 *)(scratch + 0x102) = (s16)((((u16)*(u32 *)(scratch + 0x038) + 0x100) & 0x1FF) + (temp_h18 = (s32)((S_800C6B40_0 *)arg2)->unk_18 - 0x100));
        a0p = scratch + 0x100;
        ASM_CLOBBER("$5");   /* MATCH pin: retail register colouring depends on it */
        temp_v0_3 = ((S_800C6B40_0 *)arg2)->unk_20;
        *(u32 *)(scratch + 0x0E4) = temp_v0_3;
        *(u16 *)(scratch + 0x108) = temp_v0_3;
        temp_v0_4 = (*(u16 *)((u8 *)arg2 + 0x22));
        *(u32 *)(scratch + 0x0E8) = temp_v0_4;
        *(u16 *)(scratch + 0x10A) = temp_v0_4;
        func_80065820(a0p, scratch + 0xD0, *(s16 *)(dtail + 0xC8));
        *(u32 *)(scratch + 0x030) = (void *)((S_800C6B40_0 *)arg2)->unk_1C;
        *(u32 *)(scratch + 0x034) = (void *)(*(u16 *)((u8 *)arg2 + 0x1E));
        *(u32 *)(scratch + 0x038) = NULL;
        func_80064BC0(scratch + 0xD0, scratch + 0x30);
        func_80064840((s32 *)var_s2, scratch + 0xD0, scratch + 0x50);
        func_80064D80(scratch + 0x50);
        func_80064CF0(scratch + 0x50);
        temp_h14 = ((S_800C6B40_0 *)arg2)->unk_14;
        var_s3 = ((S_800C6B40_0 *)arg2)->unk_08;
        *(u16 *)(scratch + 0x024) = (u16)temp_h14;
        do {
        if (!(((S_800C6B40_1 *)var_s3)->unk_00 & 0x20)) {
            *(u32 *)(scratch + 0x008) = (s32)((S_800C6B40_1 *)var_s3)->unk_08.at00.v;
            *(u32 *)(scratch + 0x00C) = (s32)((S_800C6B40_1 *)var_s3)->unk_08.at01.v;
            *(u32 *)(scratch + 0x010) = (s32)((S_800C6B40_1 *)var_s3)->unk_08.at02.v;
            *(u32 *)(scratch + 0x014) = (s32)((S_800C6B40_1 *)var_s3)->unk_08.at03.v;
            if ((((S_800C6B40_1 *)var_s3)->unk_00 ^ (u32)*(u16 *)(scratch + 0x024)) & 1) {
                temp_v0_7 = (0 - (s8)(*(volatile u8 *)((u8 *)var_s3 + 2))) - (s32)(u32)*(volatile u16 *)(scratch + 0x108);
                temp_d10a = *(u16 *)(scratch + 0x010);
                *(u16 *)(scratch + 0x080) = temp_v0_7;
                *(u16 *)(scratch + 0x070) = temp_v0_7;
                temp_v0_7 -= temp_d10a;
            } else {
                temp_v0_7 = (s8)(*(volatile u8 *)((u8 *)var_s3 + 2)) - (s32)(u32)*(volatile u16 *)(scratch + 0x108);
                temp_d10b = *(u16 *)(scratch + 0x010);
                *(u16 *)(scratch + 0x080) = temp_v0_7;
                *(u16 *)(scratch + 0x070) = temp_v0_7;
                temp_v0_7 += temp_d10b;
            }
            *(u16 *)(scratch + 0x088) = temp_v0_7;
            *(u16 *)(scratch + 0x078) = temp_v0_7;
            if ((((S_800C6B40_1 *)var_s3)->unk_00 ^ (u32)*(u16 *)(scratch + 0x024)) & 2) {
                temp_v0_10 = (0 - (s8)(*(volatile u8 *)((u8 *)var_s3 + 3))) - (s32)(u32)*(volatile u16 *)(scratch + 0x10A);
                temp_d14a = *(u16 *)(scratch + 0x014);
                *(u16 *)(scratch + 0x07A) = temp_v0_10;
                *(u16 *)(scratch + 0x072) = temp_v0_10;
                temp_v0_10 -= temp_d14a;
            } else {
                temp_v0_10 = (s8)(*(volatile u8 *)((u8 *)var_s3 + 3)) - (s32)(u32)*(volatile u16 *)(scratch + 0x10A);
                temp_d14b = *(u16 *)(scratch + 0x014);
                *(u16 *)(scratch + 0x07A) = temp_v0_10;
                *(u16 *)(scratch + 0x072) = temp_v0_10;
                temp_v0_10 += temp_d14b;
            }
            *(u16 *)(scratch + 0x08A) = temp_v0_10;
            *(u16 *)(scratch + 0x082) = temp_v0_10;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            func_800654B0(scratch + 0x70, scratch + 0x78, scratch + 0x80, scratch + 0x88, scratch + 0xF0, scratch + 0xF4, scratch + 0xF8, scratch + 0xFC, scratch + 0x90, scratch + 0x94);
            var_v0 = *(u32 *)(scratch + 0x010);
            if (var_v0 < 0) {
                var_v0 += 3;
            }
            var_a0 = *(u32 *)(scratch + 0x014);
            var_t5 = var_v0 >> 2;
            if (var_a0 < 0) {
                var_a0 += 3;
            }
            temp_v0_11 = (s16)*(u16 *)(scratch + 0x0F4) - (s16)*(u16 *)(scratch + 0x0F0);
            var_a1 = temp_v0_11 << 0x10;
            var_t6 = var_a0 >> 2;
            if (var_a1 < 0) {
                var_a1 += 3;
            }
            temp_v1 = *(u16 *)(scratch + 0x0F2);
            temp_v0_12 = (s16)*(u16 *)(scratch + 0x0FA) - (s16)temp_v1;
            var_a0_2 = temp_v0_12 << 0x10;
            var_t3 = var_a1 >> 2;
            if (var_a0_2 < 0) {
                var_a0_2 += 3;
            }
            temp_v0_13 = (s16)*(u16 *)(scratch + 0x0FC) - (s16)*(u16 *)(scratch + 0x0F8);
            var_a1_2 = temp_v0_13 << 0x10;
            var_t4 = var_a0_2 >> 2;
            if (var_a1_2 < 0) {
                var_a1_2 += 3;
            }
            temp_v1_2 = *(u16 *)(scratch + 0x0F6);
            temp_v0_14 = (s16)*(u16 *)(scratch + 0x0FE) - (s16)temp_v1_2;
            var_a0_3 = temp_v0_14 << 0x10;
            var_t2 = var_a1_2 >> 2;
            if (var_a0_3 < 0) {
                var_a0_3 += 3;
            }
            var_t1 = 0;
            var_t8 = var_a0_3 >> 2;
            temp_v0_15 = *(u16 *)(scratch + 0x0BA);
            var_s4 = *(u32 *)(scratch + 0x00C);
            var_s7 = ((s16)temp_v0_15 + (s16)temp_v1) << 0x10;
            var_a3 = ((s16)temp_v0_15 + (s16)temp_v1_2) << 0x10;
            var_a2 = var_a3 + var_t8;
        do {
            var_fp = 0;
            var_t0 = var_a2 >> 0x10;
            var_t7 = (var_t0 + 0x20) & 0xFFFF;
            temp_a0 = *(u16 *)(scratch + 0x0B8);
            var_s2 = *(u32 *)(scratch + 0x008);
            var_s0 = sp28 + 7;
            inner_f0 = *(u16 *)(scratch + 0x0F0);
            var_s6 = ((s16)temp_a0 + (s16)inner_f0) << 0x10;
            var_s5 = ((s16)temp_a0 + (s16)*(u16 *)(scratch + 0x0F8)) << 0x10;
            do {
                var_a1_3 = 0;
                (*(u16 *)((u8 *)var_s0 + 1)) = (u16)(var_s6 >> 0x10);
                (*(u16 *)((u8 *)var_s0 + 9)) = (u16)((s32)(var_s6 + var_t3) >> 0x10);
                (*(u16 *)((u8 *)var_s0 + 0x11)) = (u16)(var_s5 >> 0x10);
                (*(u16 *)((u8 *)var_s0 + 0x19)) = (u16)((s32)(var_s5 + var_t2) >> 0x10);
                (*(u16 *)((u8 *)var_s0 + 3)) = (u16)(var_s7 >> 0x10);
                (*(u16 *)((u8 *)var_s0 + 0xB)) = (u16)(var_a3 >> 0x10);
                (*(u16 *)((u8 *)var_s0 + 0x13)) = (u16)((s32)(var_s7 + var_t4) >> 0x10);
                (*(s16 *)((u8 *)var_s0 + 0x1B)) = (s16)var_t0;
                if ((u32)(((*(u16 *)((u8 *)var_s0 + 1)) + 0x20) & 0xFFFF) < 0x181U) {
                    temp_u = ((*(u16 *)((u8 *)var_s0 + 3)) + 0x20) & 0xFFFF;
                    var_a1_3 = temp_u < 0x121U;
                }
                var_v1 = 0;
                if ((u32)(((*(u16 *)((u8 *)var_s0 + 9)) + 0x20) & 0xFFFF) < 0x181U) {
                    temp_u = ((*(u16 *)((u8 *)var_s0 + 0xB)) + 0x20) & 0xFFFF;
                    var_v1 = temp_u < 0x121U;
                }
                var_a0_4 = 0;
                temp_a1 = var_a1_3 | var_v1;
                if ((u32)(((*(u16 *)((u8 *)var_s0 + 0x11)) + 0x20) & 0xFFFF) < 0x181U) {
                    temp_u = ((*(u16 *)((u8 *)var_s0 + 0x13)) + 0x20) & 0xFFFF;
                    var_a0_4 = temp_u < 0x121U;
                }
                var_v1_2 = 0;
                temp_a1b = temp_a1 | var_a0_4;
                if ((u32)(((*(u16 *)((u8 *)var_s0 + 0x19)) + 0x20) & 0xFFFF) < 0x181U) {
                    var_v1_2 = var_t7 < 0x121U;
                }
                if ((temp_a1b | var_v1_2) != 0) {
                    temp_v1_3 = ((S_800C6B40_0 *)arg2)->unk_0C.at03.v;
                    var_a0_5 = (var_s2 + var_t5) - temp_v1_3;
                    if (var_s2 >= var_a0_5) {
                        var_a0_5 = var_s2 + 1;
                    }
                    var_v1_3 = (var_s4 + var_t6) - temp_v1_3;
                    if (var_s4 >= var_v1_3) {
                        var_v1_3 = var_s4 + 1;
                    }
                    if (var_a0_5 >= 0x100) {
                        var_a0_5 = 0xFF;
                    }
                    if (var_v1_3 >= 0x100) {
                        var_v1_3 = 0xFF;
                    }
                    ((S_800C6B40_2 *)var_s0)->unk_05 = (s8)var_s2;
                    ((S_800C6B40_2 *)var_s0)->unk_06 = (s8)var_s4;
                    ((S_800C6B40_2 *)var_s0)->unk_0D = (s8)var_a0_5;
                    ((S_800C6B40_2 *)var_s0)->unk_0E = (s8)var_s4;
                    ((S_800C6B40_2 *)var_s0)->unk_15 = (s8)var_s2;
                    ((S_800C6B40_2 *)var_s0)->unk_16 = (s8)var_v1_3;
                    ((S_800C6B40_2 *)var_s0)->unk_1D = (s8)var_a0_5;
                    ((S_800C6B40_2 *)var_s0)->unk_1E = (s8)var_v1_3;
                    ((S_800C6B40_2_pre *)var_s0)[-1].unk_00 = 9;
                    temp_h12 = ((S_800C6B40_0 *)arg2)->unk_12;
                    ((S_800C6B40_0 *)arg2)->unk_14 = (u16)(((S_800C6B40_0 *)arg2)->unk_14 & 0x7FFF);
                    temp_h12 += ((S_800C6B40_1 *)var_s3)->unk_06;
                    (*(s16 *)((u8 *)var_s0 + 7)) = (s16)temp_h12;
                    if (((S_800C6B40_0 *)arg2)->unk_10 != 0) {
                        temp_v0_15 = ((S_800C6B40_0 *)arg2)->unk_10 + (((S_800C6B40_1 *)var_s3)->unk_04 & 0xFF9F);
                    } else {
                        temp_v0_15 = ((S_800C6B40_1 *)var_s3)->unk_04;
                    }
                    (*(u16 *)((u8 *)var_s0 + 0xF)) = temp_v0_15;
                    (*(s32 *)((u8 *)var_s0 + -3)) = (s32)((S_800C6B40_0 *)arg2)->unk_0C.at00.v;
                    ((S_800C6B40_2 *)var_s0)->unk_00 = 0x2C;
                    temp_v1_4 = *(u16 *)(scratch + 0x024);
                    if (temp_v1_4 & 8) {
                        if (!(temp_v1_4 & 4)) {
                            var_v0_2 = 0x2C;
                            ((S_800C6B40_2 *)var_s0)->unk_00 = var_v0_2;
                        } else {
                            var_v0_2 = 0x2E;
                            ((S_800C6B40_2 *)var_s0)->unk_00 = var_v0_2;
                        }
                    }
                    temp_a1_2 = sp28;
                    sp28 = temp_a1_2 + 0x28;
                    var_s0 += 0x28;
                    func_8006658C((u8 *)*(u32 *)(scratch + 0x020) + ((u32)*(u32 *)(scratch + 0x0C0) * 4), temp_a1_2);
                }
                var_fp += 1;
                var_s2 += var_t5;
                var_s6 += var_t3;
                var_s5 += var_t2;
            } while (var_fp < 4);
            var_t1 += 1;
            var_s4 += var_t6;
            var_s7 += var_t4;
            tmp_v0 = var_a2;
            ASM_KEEP_NV(tmp_v0);   /* MATCH pin: retail keeps a computation the compiler would drop */
            var_a3 = tmp_v0;
            var_a2 += var_t8;
        } while (var_t1 < 4);
        } else {
        temp_v0_16 = (s32 (*)(s32, void *, void *, void *, s32))((S_800C6B40_1 *)var_s3)->unk_08.at00u.v;
        if (temp_v0_16 != NULL) {
            var_v1 = temp_v0_16(arg0, arg1, arg2, var_s3, sp28);
            var_v0 = 0x80000000;
            if (var_v1 > 0) {
                var_s3 = (void *)(var_v1 | var_v0);
            } else {
                sp28 = var_v1;
            }
        }
        }
        temp_last = (s8)((S_800C6B40_1 *)var_s3)->unk_00;
        var_s3 += 0xC;
        } while (temp_last >= 0);
        func_80064A40();
    }
    *(s32 *)(*(u32 *)dtail + 0x8D0) = sp28;
}
