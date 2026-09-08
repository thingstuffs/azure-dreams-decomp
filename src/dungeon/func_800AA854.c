#include "common.h"

typedef struct S_800AFFB4_0 {
    u8 pad_00[0x8];
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
} S_800AFFB4_0;   /* arg0 in func_800AFFB4 */

typedef struct S_800AFFB4_1 {
    u8 pad_00[0x8];
    union { volatile s32 s32; volatile u16 u16; } unk_08;   /* accessed as both */
    volatile s32 unk_0C;
    union { volatile s32 s32; volatile u16 u16; } unk_10;   /* accessed as both */
    union { volatile s32 s32; volatile u16 u16; } unk_14;   /* accessed as both */
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
    union { s32 s32; u16 u16; } unk_90;   /* accessed as both */
    u8 pad_94[0x5C];
    union { struct { u16 v; } at00; struct { s32 v; } at00u; struct { s16 v; } at00p; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_F0;   /* overlapping accesses */
    union { struct { u16 v; } at00; struct { s32 v; } at00u; struct { s16 v; } at00p; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_F4;   /* overlapping accesses */
    union { struct { u16 v; } at00; struct { s32 v; } at00u; struct { s16 v; } at00p; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_F8;   /* overlapping accesses */
    union { struct { u16 v; } at00; struct { s32 v; } at00u; struct { s16 v; } at00p; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_FC;   /* overlapping accesses */
    u8 pad_100[0x18];
    s32 unk_118;
} S_800AFFB4_1;   /* arg2 in func_800AFFB4 */

typedef struct S_800AFFB4_2_pre {
    s8 unk_00;
    u8 pad_01[0x3];
    s32 unk_04;
    u8 pad_08[0x4];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u8 pad_14[0x4];
    s8 unk_18;
    s8 unk_19;
    s8 unk_1A;
    u8 pad_1B[0x1];
    s32 unk_1C;
    u8 pad_20[0x4];
    s8 unk_24;
    s8 unk_25;
    s8 unk_26;
    u8 pad_27[0x1];
    s16 unk_28;
    s16 unk_2A;
    u8 pad_2C[0x8];
    s8 unk_34;
    s8 unk_35;
    s8 unk_36;
    u8 pad_37[0x1];
    s16 unk_38;
    s16 unk_3A;
    u8 pad_3C[0x4];
    s8 unk_40;
    s8 unk_41;
    s8 unk_42;
    u8 pad_43[0x1];
    s32 unk_44;
    u8 pad_48[0x4];
} S_800AFFB4_2_pre;   /* the 0x4C bytes before var_s2 in func_800AFFB4, addressed as var_s2[-1] */

typedef struct S_800AFFB4_2 {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
    u8 pad_03[0x1];
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x4];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s32 unk_10;
} S_800AFFB4_2;   /* var_s2 in func_800AFFB4 */

typedef struct S_800AFFB4_3 {
    s16 unk_00;
    u16 unk_02;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
} S_800AFFB4_3;   /* var_s3 in func_800AFFB4 */

typedef struct S_800AFFB4_4_pre {
    union { volatile u8 v; volatile s8 v2; } unk_00;   /* accessed as both */
    u8 pad_01[0xC];
    volatile u8 unk_0D;
    u8 pad_0E[0xA];
    union { volatile u8 v; volatile s8 v2; } unk_18;   /* accessed as both */
} S_800AFFB4_4_pre;   /* the 0x19 bytes before var_s0 in func_800AFFB4, addressed as var_s0[-1] */

typedef struct S_800AFFB4_4 {
    volatile u8 unk_00;
} S_800AFFB4_4;   /* var_s0 in func_800AFFB4 */



typedef struct ShortArg {
    u16 value;
} ShortArg;

typedef struct TwelveByteEntry {
    u8 bytes[12];
} TwelveByteEntry;

extern s32 func_80065610();
extern void func_8006658C();
extern void func_8006671C();

s32 func_800AFFB4(void *arg0, void *arg1, void *arg2_in, u8 *arg3, volatile ShortArg arg4) {
    s32 var_a0_2;
    register s32 temp_a0_2 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 temp_a0_3;
    register s32 temp_a1_2 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 temp_a2;
    register s32 inner_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 inner_v1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 var_a0;
    s32 var_a1;
    register void *arg2 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 var_fp;
    TwelveByteEntry *var_s4;
    s32 var_s5;
    register u8 *var_s6 ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 var_s7;
    s32 var_v0;
    s32 var_v1;
    u16 temp_v0_2;
    s32 flagv;
    u16 sp30;
    u16 sp38;
    u32 temp_hi;
    register u8 *var_s0 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    u8 *var_s2;
    register u8 *var_s3 ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

    (void)arg1;
    arg2 = arg2_in;
    var_s6 = arg3;
    var_fp = 0;
    var_s7 = 0;
    var_s2 = var_s6 + 0x50;
    ASM_KEEP(arg2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    flagv = ((S_800AFFB4_0 *)arg0)->unk_08.s;
    flagv = flagv < 0xE00;
    sp30 = arg4.value;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    inner_v1 = ((S_800AFFB4_0 *)arg0)->unk_08.u;
    flagv ^= 1;
    sp38 = flagv;
    inner_v0 = inner_v1 - 0x6200;
    inner_v1 -= 0x5400;
    ((S_800AFFB4_1 *)arg2)->unk_7C = inner_v0;
    ((S_800AFFB4_1 *)arg2)->unk_74 = inner_v0;
    ((S_800AFFB4_1 *)arg2)->unk_8C = inner_v1;
    ((S_800AFFB4_1 *)arg2)->unk_84 = inner_v1;
loop_1:
    ((S_800AFFB4_1 *)arg2)->unk_74 = ((S_800AFFB4_1 *)arg2)->unk_74 + 0xE00;
    ((S_800AFFB4_1 *)arg2)->unk_7C = ((S_800AFFB4_1 *)arg2)->unk_7C + 0xE00;
    ((S_800AFFB4_1 *)arg2)->unk_84 = ((S_800AFFB4_1 *)arg2)->unk_84 + 0xE00;
    ((S_800AFFB4_1 *)arg2)->unk_8C = ((S_800AFFB4_1 *)arg2)->unk_8C + 0xE00;
    if (func_80065610((u8 *)arg2 + 0x70, (u8 *)arg2 + 0x78,
            (u8 *)arg2 + 0x80, (u8 *)arg2 + 0x88,
            (u8 *)arg2 + 0xF0, (u8 *)arg2 + 0xF4,
            (u8 *)arg2 + 0xF8, (u8 *)arg2 + 0xFC,
            (u8 *)arg2 + 0x90, (u8 *)arg2 + 0xC0,
            (u8 *)arg2 + 0x94) > 0) {
        var_a1 = 0;
        if ((u32)((((S_800AFFB4_1 *)arg2)->unk_F0.at00.v + 0x20) & 0xFFFF) < 0x181U) {
            temp_v0_2 = ((S_800AFFB4_1 *)arg2)->unk_F0.at02.v + 0x20;
            var_a1 = temp_v0_2 < 0x121U;
        }
        var_v1 = 0;
        if ((u32)((((S_800AFFB4_1 *)arg2)->unk_F4.at00.v + 0x20) & 0xFFFF) < 0x181U) {
            temp_v0_2 = ((S_800AFFB4_1 *)arg2)->unk_F4.at02.v + 0x20;
            var_v1 = temp_v0_2 < 0x121U;
        }
        var_a0 = 0;
        temp_v0_3 = (u32)((((S_800AFFB4_1 *)arg2)->unk_F8.at00.v + 0x20) & 0xFFFF) < 0x181U;
        var_a1 |= var_v1;
        if (temp_v0_3) {
            temp_v0_2 = ((S_800AFFB4_1 *)arg2)->unk_F8.at02.v + 0x20;
            var_a0 = temp_v0_2 < 0x121U;
        }
        var_v1 = 0;
        temp_v0_3 = (u32)((((S_800AFFB4_1 *)arg2)->unk_FC.at00.v + 0x20) & 0xFFFF) < 0x181U;
        temp_a0_2 = var_a1 | var_a0;
        var_a0 = temp_a0_2;
        if (temp_v0_3) {
            temp_v0_2 = ((S_800AFFB4_1 *)arg2)->unk_FC.at02.v + 0x20;
            var_v1 = temp_v0_2 < 0x121U;
        }
        if ((var_a0 | var_v1) != 0) {
            ((S_800AFFB4_2_pre *)var_s2)[-1].unk_04 = ((S_800AFFB4_1 *)arg2)->unk_F0.at00u.v;
            ((S_800AFFB4_2_pre *)var_s2)[-1].unk_1C = ((S_800AFFB4_1 *)arg2)->unk_F8.at00u.v;
            ((S_800AFFB4_2_pre *)var_s2)[-1].unk_44 = ((S_800AFFB4_1 *)arg2)->unk_F4.at00u.v;
            ((S_800AFFB4_2 *)var_s2)->unk_10 = ((S_800AFFB4_1 *)arg2)->unk_FC.at00u.v;
            temp_v0_3 = (((S_800AFFB4_1 *)arg2)->unk_F0.at00p.v + ((S_800AFFB4_1 *)arg2)->unk_F4.at00p.v) >> 1;
            ((S_800AFFB4_2_pre *)var_s2)[-1].unk_38 = temp_v0_3;
            ((S_800AFFB4_2_pre *)var_s2)[-1].unk_10 = temp_v0_3;
            temp_v0_4 = (((S_800AFFB4_1 *)arg2)->unk_F8.at00p.v + ((S_800AFFB4_1 *)arg2)->unk_FC.at00p.v) >> 1;
            ((S_800AFFB4_2 *)var_s2)->unk_04 = temp_v0_4;
            ((S_800AFFB4_2_pre *)var_s2)[-1].unk_28 = temp_v0_4;
            temp_v0_5 = (((S_800AFFB4_1 *)arg2)->unk_F0.at02u.v + ((S_800AFFB4_1 *)arg2)->unk_F4.at02u.v) >> 1;
            ((S_800AFFB4_2_pre *)var_s2)[-1].unk_3A = temp_v0_5;
            ((S_800AFFB4_2_pre *)var_s2)[-1].unk_12 = temp_v0_5;
            temp_v0_6 = (((S_800AFFB4_1 *)arg2)->unk_F8.at02u.v + ((S_800AFFB4_1 *)arg2)->unk_FC.at02u.v) >> 1;
            ((S_800AFFB4_2 *)var_s2)->unk_06 = temp_v0_6;
            ((S_800AFFB4_2_pre *)var_s2)[-1].unk_2A = temp_v0_6;
            var_a0_2 = (s16)((S_800AFFB4_1 *)arg2)->unk_74 % 3584;
            ((S_800AFFB4_1 *)arg2)->unk_90.s32 = var_a0_2;
            if (var_a0_2 < 0) {
                var_a0_2 += 0xFF;
            }
            var_a0_2 >>= 8;
            ((S_800AFFB4_1 *)arg2)->unk_90.s32 = var_a0_2;
            inner_v0 = sp38;
            if (inner_v0 != 0) {
                ((S_800AFFB4_1 *)arg2)->unk_90.s32 = var_a0_2 + 0x10;
            }
            temp_a0_2 = 0x80;
            inner_v1 = ((S_800AFFB4_1 *)arg2)->unk_90.u16;
            inner_v0 = var_s7 << 4;
            inner_v1 += inner_v0;
            inner_v0 = 0xE0;
            temp_a1_2 = inner_v0 - inner_v1;
            inner_v0 = temp_a1_2 << 0x10;
            temp_a2 = inner_v0 >> 0x10;
            inner_v1 = temp_a1_2;
            if (temp_a2 < 0x81) {
                temp_a0_2 = temp_a1_2;
                if (temp_a2 < 0) {
                    temp_a0_2 = 0;
                }
            }
            inner_v0 = inner_v1 - 0x10;
            inner_v1 = inner_v0;
            inner_v0 <<= 0x10;
            (*(s8 *)((u8 *)var_s2 + -0x4A)) = temp_a0_2;
            ((S_800AFFB4_2_pre *)var_s2)[-1].unk_0E = temp_a0_2;
            ((S_800AFFB4_2_pre *)var_s2)[-1].unk_42 = temp_a0_2;
            ((S_800AFFB4_2_pre *)var_s2)[-1].unk_36 = temp_a0_2;
            (*(s8 *)((u8 *)var_s2 + -0x4B)) = temp_a0_2;
            ((S_800AFFB4_2_pre *)var_s2)[-1].unk_0D = temp_a0_2;
            ((S_800AFFB4_2_pre *)var_s2)[-1].unk_41 = temp_a0_2;
            ((S_800AFFB4_2_pre *)var_s2)[-1].unk_35 = temp_a0_2;
            ((S_800AFFB4_2_pre *)var_s2)[-1].unk_00 = temp_a0_2;
            ((S_800AFFB4_2_pre *)var_s2)[-1].unk_0C = temp_a0_2;
            ((S_800AFFB4_2_pre *)var_s2)[-1].unk_40 = temp_a0_2;
            ((S_800AFFB4_2_pre *)var_s2)[-1].unk_34 = temp_a0_2;
            temp_a0_2 = inner_v0 >> 0x10;
            if (temp_a0_2 >= 0x81) {
                inner_v1 = 0x80;
                goto local_s5_zero;
            }
            var_s5 = 0;
            if (temp_a0_2 < 0) {
                inner_v1 = 0;
            }
local_s5_zero:
            var_s5 = 0;
            var_s0 = var_s6 + 0x31;
            ((S_800AFFB4_2_pre *)var_s2)[-1].unk_1A = inner_v1;
            ((S_800AFFB4_2_pre *)var_s2)[-1].unk_26 = inner_v1;
            ((S_800AFFB4_2 *)var_s2)->unk_0E = inner_v1;
            ((S_800AFFB4_2 *)var_s2)->unk_02 = inner_v1;
            ((S_800AFFB4_2_pre *)var_s2)[-1].unk_19 = inner_v1;
            ((S_800AFFB4_2_pre *)var_s2)[-1].unk_25 = inner_v1;
            ((S_800AFFB4_2 *)var_s2)->unk_0D = inner_v1;
            ((S_800AFFB4_2 *)var_s2)->unk_01 = inner_v1;
            ((S_800AFFB4_2_pre *)var_s2)[-1].unk_18 = inner_v1;
            ((S_800AFFB4_2_pre *)var_s2)[-1].unk_24 = inner_v1;
            ((S_800AFFB4_2 *)var_s2)->unk_0C = inner_v1;
            ((S_800AFFB4_2 *)var_s2)->unk_00 = inner_v1;
            inner_v1 = var_s7 & 1;
            ASM_KEEP(inner_v1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            inner_v1 <<= 1;
            inner_v0 = (s32)(sp30 << 0x10) >> 0xE;
            inner_v1 += inner_v0;
            inner_v0 = inner_v1 << 1;
            inner_v0 += inner_v1;
            inner_v1 = ((S_800AFFB4_1 *)arg2)->unk_118;
            inner_v0 <<= 2;
            var_s4 = (TwelveByteEntry *)((u8 *)inner_v1 + inner_v0);
            var_s3 = (u8 *)var_s4 + 4;
            do {
                func_8006671C(var_s6);
                ((S_800AFFB4_1 *)arg2)->unk_08.s32 = ((S_800AFFB4_3 *)var_s3)->unk_04;
                temp_a1_2 = ((S_800AFFB4_1 *)arg2)->unk_08.s32;
                ((S_800AFFB4_1 *)arg2)->unk_0C = ((S_800AFFB4_3 *)var_s3)->unk_05;
                temp_a0_2 = ((S_800AFFB4_1 *)arg2)->unk_0C;
                ((S_800AFFB4_1 *)arg2)->unk_10.s32 = ((S_800AFFB4_3 *)var_s3)->unk_06;
                inner_v1 = temp_a0_2;
                temp_a0_3 = ((S_800AFFB4_3 *)var_s3)->unk_07;
                temp_a0_2 <<= 8;
                ((S_800AFFB4_1 *)arg2)->unk_0C = temp_a0_2;
                ((S_800AFFB4_1 *)arg2)->unk_14.s32 = temp_a0_3;
                temp_v0_3 = ((S_800AFFB4_1 *)arg2)->unk_10.s32;
                temp_a2 = ((S_800AFFB4_1 *)arg2)->unk_14.s32;
                temp_v0_3 += temp_a1_2;
                inner_v1 += temp_a2;
                inner_v1 <<= 8;
                ((S_800AFFB4_1 *)arg2)->unk_14.s32 = inner_v1;
                inner_v1 = temp_a1_2;
                ASM_KEEP(inner_v1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                ((S_800AFFB4_1 *)arg2)->unk_10.s32 = temp_v0_3;
                inner_v0 = ((S_800AFFB4_3 *)var_s3)->unk_02;
                temp_a0_2 += inner_v1;
                inner_v0 <<= 0x10;
                temp_a0_2 |= inner_v0;
                (*(s32 *)((u8 *)var_s0 + -0x25)) = temp_a0_2;
                inner_v0 = ((S_800AFFB4_1 *)arg2)->unk_0C;
                temp_a0_2 = ((S_800AFFB4_1 *)arg2)->unk_10.s32;
                inner_v1 = ((S_800AFFB4_3 *)var_s3)->unk_00;
                inner_v0 += temp_a0_2;
                inner_v1 <<= 0x10;
                inner_v0 |= inner_v1;
                (*(s32 *)((u8 *)var_s0 + -0x19)) = inner_v0;
                inner_v0 = ((S_800AFFB4_1 *)arg2)->unk_14.u16;
                inner_v1 = ((S_800AFFB4_1 *)arg2)->unk_08.u16;
                ASM_KEEP(inner_v0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                inner_v0 += inner_v1;
                (*(volatile s16 *)((u8 *)var_s0 + -0xD)) = inner_v0;
                inner_v1 = ((S_800AFFB4_1 *)arg2)->unk_14.u16;
                inner_v0 = ((S_800AFFB4_4_pre *)var_s0)[-1].unk_00.v;
                temp_a0_2 = ((S_800AFFB4_1 *)arg2)->unk_10.u16;
                ASM_KEEP(inner_v0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                inner_v0 -= 1;
                inner_v1 += temp_a0_2;
                ((S_800AFFB4_4_pre *)var_s0)[-1].unk_00.v2 = inner_v0;
                (*(volatile s16 *)((u8 *)var_s0 + -1)) = inner_v1;
                inner_v0 = ((S_800AFFB4_4_pre *)var_s0)[-1].unk_18.v;
                inner_v1 = ((S_800AFFB4_4_pre *)var_s0)[-1].unk_0D;
                inner_v0 -= 1;
                inner_v1 -= 1;
                ((S_800AFFB4_4_pre *)var_s0)[-1].unk_18.v2 = inner_v0;
                ((S_800AFFB4_4_pre *)var_s0)[-1].unk_0D = inner_v1;
                inner_v0 = ((S_800AFFB4_4 *)var_s0)->unk_00;
                inner_v0 -= 1;
                ((S_800AFFB4_4 *)var_s0)->unk_00 = inner_v0;
                inner_v1 = ((S_800AFFB4_1 *)arg2)->unk_118;
                temp_hi = (u32)(var_s4 - (TwelveByteEntry *)inner_v1) / 12;
                var_s2 += 0x34;
                var_s5 += 1;
                temp_a1_2 = (s32)var_s6;
                var_s3 += 0xC;
                var_s0 += 0x34;
                var_s4 += 1;
                func_8006658C(((S_800AFFB4_1 *)arg2)->unk_20 + (temp_hi * 4),
                    (void *)temp_a1_2, temp_a2);
                var_s6 += 0x34;
            } while (var_s5 < 2);
            var_fp += 1;
            goto block_26;
        }
        goto block_26;
    }
block_26:
    var_s7 += 1;
    if (var_s7 >= 0xE) {
        var_v0 = 0;
        if (var_fp != 0) {
            var_v0 = (s32)var_s6;
        }
        return var_v0;
    }
    goto loop_1;
}
