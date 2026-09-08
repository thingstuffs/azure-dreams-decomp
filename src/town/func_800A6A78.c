#include "common.h"

typedef struct S_800A41D8_0 {
    u8 pad_00[0x8];
    u16 unk_08;
    u8 pad_0A[0xC];
    u16 unk_16;
} S_800A41D8_0;   /* arg0 in func_800A41D8 */

typedef struct S_800A41D8_1 {
    u8 pad_00[0x8];
    union { s32 n; volatile s32 v; } unk_08;   /* accessed as both */
    union { s32 n; volatile s32 v; } unk_0C;   /* accessed as both */
    s32 unk_10;
    union { s32 n; volatile s32 v; } unk_14;   /* accessed as both */
    u8 pad_18[0x8];
    s32 unk_20;
    u8 pad_24[0x50];
    u16 unk_74;
    u8 pad_76[0x6];
    u16 unk_7C;
    u8 pad_7E[0x6];
    u16 unk_84;
    u8 pad_86[0x6];
    u16 unk_8C;
    u8 pad_8E[0x2];
    s32 unk_90;
    u8 pad_94[0x5C];
    union { struct { u16 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_F0;   /* overlapping accesses */
    union { struct { u16 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_F4;   /* overlapping accesses */
    union { struct { u16 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_F8;   /* overlapping accesses */
    union { struct { u16 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_FC;   /* overlapping accesses */
    u8 pad_100[0x18];
    s32 unk_118;
} S_800A41D8_1;   /* state in func_800A41D8 */

typedef struct S_800A41D8_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    s8 unk_06;
    u8 pad_07[0x1];
    s32 unk_08;
    u8 pad_0C[0x4];
    s16 unk_10;
    s16 unk_12;
    u8 pad_14[0x4];
    s32 unk_18;
    u8 pad_1C[0x4];
    s16 unk_20;
    s16 unk_22;
    u8 pad_24[0x8];
    s8 unk_2C;
    u8 pad_2D[0xB];
    s32 unk_38;
    u8 pad_3C[0xC];
    s32 unk_48;
} S_800A41D8_2;   /* var_s3 in func_800A41D8 */

typedef struct S_800A41D8_3 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
    u8 pad_0C[0xC];
    s16 unk_18;
    s16 unk_1A;
} S_800A41D8_3;   /* temp_a0 in func_800A41D8 */

typedef struct S_800A41D8_4 {
    u8 pad_00[0x5];
    s8 unk_05;
    s8 unk_06;
} S_800A41D8_4;   /* temp_v0_7 in func_800A41D8 */

typedef struct S_800A41D8_5_pre {
    u8 unk_00;
    u8 pad_01[0xC];
    u8 unk_0D;
    u8 pad_0E[0x8];
    u8 unk_16;
    u8 pad_17[0x6];
    u8 unk_1D;
} S_800A41D8_5_pre;   /* the 0x1E bytes before var_s0 in func_800A41D8, addressed as var_s0[-1] */

typedef struct S_800A41D8_5 {
    u8 unk_00;
} S_800A41D8_5;   /* var_s0 in func_800A41D8 */

typedef struct S_800A41D8_6 {
    u8 pad_00[0xF];
    u8 unk_0F;
} S_800A41D8_6;   /* arg1 in func_800A41D8 */

typedef struct S_800A41D8_7 {
    s16 unk_00;
    u16 unk_02;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
} S_800A41D8_7;   /* var_s2 in func_800A41D8 */


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
    register s32 var_a0_3 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 var_v1_3;
    register s32 temp_a0_2 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 var_copy;
    s32 temp_a0_4;
    s32 temp_a0_5;
    register s32 temp_a1_2 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 temp_a2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
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
    register s32 temp_dec ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u16 tsum;
    u16 temp_v0_2;
    u16 temp_v1;
    u32 temp_hi;
    void *temp_a0;
    void *temp_a1_3;
    void *temp_v0_7;
    void *var_a0;
    void *var_v0;
    register void *var_s0 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    void *state;
    register void *var_s2 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register void *var_s3 ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 var_s4;
    s32 var_s5;
    s32 var_s6;
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
    ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    temp_v0 = ((S_800A41D8_0 *)arg0)->unk_08;
    temp_v1 = temp_v0 - 0x6200;
    temp_v0_2 = temp_v0 - 0x5400;
    sp40 = ((S_800A41D8_0 *)arg0)->unk_16;
    ((S_800A41D8_1 *)state)->unk_7C = temp_v1;
    ((S_800A41D8_1 *)state)->unk_74 = temp_v1;
    ((S_800A41D8_1 *)state)->unk_8C = temp_v0_2;
    ((S_800A41D8_1 *)state)->unk_84 = temp_v0_2;
    do {
        ((S_800A41D8_1 *)state)->unk_74 = (u16) (((S_800A41D8_1 *)state)->unk_74 + 0xE00);
        ((S_800A41D8_1 *)state)->unk_7C = (u16) (((S_800A41D8_1 *)state)->unk_7C + 0xE00);
        ((S_800A41D8_1 *)state)->unk_84 = (u16) (((S_800A41D8_1 *)state)->unk_84 + 0xE00);
        ((S_800A41D8_1 *)state)->unk_8C = (u16) (((S_800A41D8_1 *)state)->unk_8C + 0xE00);
        if (func_80065610(state + 0x70, state + 0x78, state + 0x80, state + 0x88, state + 0xF0, state + 0xF4, state + 0xF8, state + 0xFC, state + 0x90, state + 0xC0, state + 0x94) > 0) {
            var_a1 = 0;
            if ((u32) ((((S_800A41D8_1 *)state)->unk_F0.at00.v + 0x20) & 0xFFFF) < 0x181U) {
                temp_bound = ((S_800A41D8_1 *)state)->unk_F0.at02.v + 0x20;
                var_a1 = temp_bound < 0x121U;
            }
            var_v1 = 0;
            if ((u32) ((((S_800A41D8_1 *)state)->unk_F4.at00.v + 0x20) & 0xFFFF) < 0x181U) {
                temp_bound = ((S_800A41D8_1 *)state)->unk_F4.at02.v + 0x20;
                var_v1 = temp_bound < 0x121U;
            }
            var_a0_2 = 0;
            var_a1 |= var_v1;
            if ((u32) ((((S_800A41D8_1 *)state)->unk_F8.at00.v + 0x20) & 0xFFFF) < 0x181U) {
                temp_bound = ((S_800A41D8_1 *)state)->unk_F8.at02.v + 0x20;
                var_a0_2 = temp_bound < 0x121U;
            }
            var_v1 = 0;
            var_a0_4 = var_a1 | var_a0_2;
            if ((u32) ((((S_800A41D8_1 *)state)->unk_FC.at00.v + 0x20) & 0xFFFF) < 0x181U) {
                temp_bound = ((S_800A41D8_1 *)state)->unk_FC.at02.v + 0x20;
                var_v1 = temp_bound < 0x121U;
            }
            if ((var_a0_4 | var_v1) != 0) {
                temp_a0 = var_s3 + 0x28;
                ((S_800A41D8_2 *)var_s3)->unk_08 = ((S_800A41D8_1 *)state)->unk_F0.at00u.v;
                ((S_800A41D8_2 *)var_s3)->unk_18 = ((S_800A41D8_1 *)state)->unk_F8.at00u.v;
                ((S_800A41D8_2 *)var_s3)->unk_38 = ((S_800A41D8_1 *)state)->unk_F4.at00u.v;
                ((S_800A41D8_2 *)var_s3)->unk_48 = ((S_800A41D8_1 *)state)->unk_FC.at00u.v;
                temp_v0_3 = (s32) ((s16) ((S_800A41D8_1 *)state)->unk_F0.at00.v + (s16) ((S_800A41D8_1 *)state)->unk_F4.at00.v) >> 1;
                ((S_800A41D8_3 *)temp_a0)->unk_08 = (s16) temp_v0_3;
                ((S_800A41D8_2 *)var_s3)->unk_10 = (s16) temp_v0_3;
                temp_v0_4 = (s32) ((s16) ((S_800A41D8_1 *)state)->unk_F8.at00.v + (s16) ((S_800A41D8_1 *)state)->unk_FC.at00.v) >> 1;
                ((S_800A41D8_3 *)temp_a0)->unk_18 = (s16) temp_v0_4;
                ((S_800A41D8_2 *)var_s3)->unk_20 = (s16) temp_v0_4;
                temp_v0_5 = (s32) ((s16) ((S_800A41D8_1 *)state)->unk_F0.at02.v + (s16) ((S_800A41D8_1 *)state)->unk_F4.at02.v) >> 1;
                ((S_800A41D8_3 *)temp_a0)->unk_0A = (s16) temp_v0_5;
                ((S_800A41D8_2 *)var_s3)->unk_12 = (s16) temp_v0_5;
                temp_v0_6 = (s32) ((s16) ((S_800A41D8_1 *)state)->unk_F8.at02.v + (s16) ((S_800A41D8_1 *)state)->unk_FC.at02.v) >> 1;
                ((S_800A41D8_3 *)temp_a0)->unk_1A = (s16) temp_v0_6;
                ((S_800A41D8_2 *)var_s3)->unk_22 = (s16) temp_v0_6;
                var_a0_3 = (s16) ((S_800A41D8_1 *)state)->unk_74 % 3584;
                ((S_800A41D8_1 *)state)->unk_90 = (s32) var_a0_3;
                if (var_a0_3 < 0) {
                    var_a0_3 += 0xFF;
                }
                temp_v0_3 = var_a0_3 >> 8;
                ((S_800A41D8_1 *)state)->unk_90 = temp_v0_3;
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
                ((S_800A41D8_2 *)var_s3)->unk_06 = (s8) var_v1_3;
                ((S_800A41D8_4 *)temp_v0_7)->unk_06 = (s8) var_v1_3;
                ((S_800A41D8_2 *)var_s3)->unk_05 = (s8) var_v1_3;
                ((S_800A41D8_4 *)temp_v0_7)->unk_05 = (s8) var_v1_3;
                ((S_800A41D8_2 *)var_s3)->unk_04 = (s8) var_v1_3;
                ((S_800A41D8_2 *)var_s3)->unk_2C = (s8) var_v1_3;
                var_s5 = ((S_800A41D8_1 *)state)->unk_118 + ((((var_s6 & 1) * 2) + ((s32) (sp38 << 0x10) >> 0xE)) * 0xC);
                var_s2 = var_s5 + 4;
                do {
                    func_800666F4(var_s3);
                    ((S_800A41D8_5_pre *)var_s0)[-1].unk_00 = (u8) (((S_800A41D8_5_pre *)var_s0)[-1].unk_00 | (((S_800A41D8_6 *)arg1)->unk_0F & 2));
                    ((S_800A41D8_1 *)state)->unk_08.n = (s32) ((S_800A41D8_7 *)var_s2)->unk_04;
                    ((S_800A41D8_1 *)state)->unk_0C.n = (s32) ((S_800A41D8_7 *)var_s2)->unk_05;
                    temp_a1_2 = ((S_800A41D8_1 *)state)->unk_08.v;
                    temp_a0_2 = ((S_800A41D8_1 *)state)->unk_0C.v;
                    ((S_800A41D8_1 *)state)->unk_10 = (s32) ((S_800A41D8_7 *)var_s2)->unk_06;
                    var_copy = temp_a0_2;
                    ((S_800A41D8_1 *)state)->unk_14.n = (s32) ((S_800A41D8_7 *)var_s2)->unk_07;
                    temp_a0_2 <<= 8;
                    ((S_800A41D8_1 *)state)->unk_0C.n = temp_a0_2;
                    temp_a2 = ((S_800A41D8_1 *)state)->unk_14.v;
                    var_copy += temp_a2;
                    var_copy <<= 8;
                    ((S_800A41D8_1 *)state)->unk_14.n = var_copy;
                    ((S_800A41D8_1 *)state)->unk_10 = (s32) (((S_800A41D8_1 *)state)->unk_10 + temp_a1_2);
                    var_copy = temp_a1_2;
                    ASM_KEEP_NV(var_copy);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    (*(s32 *)((u8 *)var_s0 + -0x19)) = (s32) ((temp_a0_2 + var_copy) | (((S_800A41D8_7 *)var_s2)->unk_02 << 0x10));
                    (*(s32 *)((u8 *)var_s0 + -0x11)) = (s32) ((((S_800A41D8_1 *)state)->unk_0C.n + ((S_800A41D8_1 *)state)->unk_10) | (((S_800A41D8_7 *)var_s2)->unk_00 << 0x10));
                    (*(s16 *)((u8 *)var_s0 + -9)) = (s16) ((u16) ((S_800A41D8_1 *)state)->unk_14.n + (u16) ((S_800A41D8_1 *)state)->unk_08.n);
                    temp_dec = ((S_800A41D8_5_pre *)var_s0)[-1].unk_0D;
                    tv14 = (u16) ((S_800A41D8_1 *)state)->unk_14.n;
                    tv10 = (u16) ((S_800A41D8_1 *)state)->unk_10;
                    tsum = tv14 + tv10;
                    do {
                        temp_dec -= 1;
                    } while (0);
                    (*(s16 *)((u8 *)var_s0 + -1)) = (s16) tsum;
                    do {
                        ((S_800A41D8_5_pre *)var_s0)[-1].unk_0D = (u8) temp_dec;
                    } while (0);
                    ((S_800A41D8_5_pre *)var_s0)[-1].unk_1D = (u8) (((S_800A41D8_5_pre *)var_s0)[-1].unk_1D - 1);
                    ((S_800A41D8_5_pre *)var_s0)[-1].unk_16 = (u8) (((S_800A41D8_5_pre *)var_s0)[-1].unk_16 - 1);
                    ((S_800A41D8_5 *)var_s0)->unk_00 = (u8) (((S_800A41D8_5 *)var_s0)->unk_00 - 1);
                    func_8006658C(((S_800A41D8_1 *)state)->unk_20 + (((u32) ((s32) (0 - ((var_s5 - ((S_800A41D8_1 *)state)->unk_118) * 0x55555555)) >> 2) / 12U) * 4), var_s3);
                    temp_hi = (u32) ((s32) (0 - ((var_s5 - ((S_800A41D8_1 *)state)->unk_118) * 0x55555555)) >> 2) / 12U;
                    var_s2 += 0xC;
                    var_s0 += 0x28;
                    var_s3 += 0x28;
                    temp_a0_4 = var_s4 * 4;
                    var_s4 += 1;
                    temp_dst = (s32 *)(temp_a0_4 + (s32) var_s7);
                    var_s5 += 0xC;
                    temp_res = ((S_800A41D8_1 *)state)->unk_20;
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
