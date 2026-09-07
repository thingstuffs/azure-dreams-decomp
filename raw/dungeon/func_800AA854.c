#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

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
    register s32 temp_a0_2 ASM_REG("$4");
    s32 temp_a0_3;
    register s32 temp_a1_2 ASM_REG("$5");
    s32 temp_a2;
    register s32 inner_v0 ASM_REG("$2");
    register s32 inner_v1 ASM_REG("$3");
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 var_a0;
    s32 var_a1;
    register void *arg2 ASM_REG("$17");
    s32 var_fp;
    TwelveByteEntry *var_s4;
    s32 var_s5;
    register u8 *var_s6 ASM_REG("$22");
    s32 var_s7;
    s32 var_v0;
    s32 var_v1;
    u16 temp_v0_2;
    s32 flagv;
    u16 sp30;
    u16 sp38;
    u32 temp_hi;
    register u8 *var_s0 ASM_REG("$16");
    u8 *var_s2;
    register u8 *var_s3 ASM_REG("$19");

    (void)arg1;
    arg2 = arg2_in;
    var_s6 = arg3;
    var_fp = 0;
    var_s7 = 0;
    var_s2 = var_s6 + 0x50;
    ASM_KEEP(arg2);
    flagv = FIELD(arg0, s16, 8);
    flagv = flagv < 0xE00;
    sp30 = arg4.value;
    ASM_SCHED_BARRIER();
    inner_v1 = FIELD(arg0, u16, 8);
    flagv ^= 1;
    sp38 = flagv;
    inner_v0 = inner_v1 - 0x6200;
    inner_v1 -= 0x5400;
    FIELD(arg2, u16, 0x7C) = inner_v0;
    FIELD(arg2, u16, 0x74) = inner_v0;
    FIELD(arg2, u16, 0x8C) = inner_v1;
    FIELD(arg2, u16, 0x84) = inner_v1;
loop_1:
    FIELD(arg2, u16, 0x74) = FIELD(arg2, u16, 0x74) + 0xE00;
    FIELD(arg2, u16, 0x7C) = FIELD(arg2, u16, 0x7C) + 0xE00;
    FIELD(arg2, u16, 0x84) = FIELD(arg2, u16, 0x84) + 0xE00;
    FIELD(arg2, u16, 0x8C) = FIELD(arg2, u16, 0x8C) + 0xE00;
    if (func_80065610((u8 *)arg2 + 0x70, (u8 *)arg2 + 0x78,
            (u8 *)arg2 + 0x80, (u8 *)arg2 + 0x88,
            (u8 *)arg2 + 0xF0, (u8 *)arg2 + 0xF4,
            (u8 *)arg2 + 0xF8, (u8 *)arg2 + 0xFC,
            (u8 *)arg2 + 0x90, (u8 *)arg2 + 0xC0,
            (u8 *)arg2 + 0x94) > 0) {
        var_a1 = 0;
        if ((u32)((FIELD(arg2, u16, 0xF0) + 0x20) & 0xFFFF) < 0x181U) {
            temp_v0_2 = FIELD(arg2, u16, 0xF2) + 0x20;
            var_a1 = temp_v0_2 < 0x121U;
        }
        var_v1 = 0;
        if ((u32)((FIELD(arg2, u16, 0xF4) + 0x20) & 0xFFFF) < 0x181U) {
            temp_v0_2 = FIELD(arg2, u16, 0xF6) + 0x20;
            var_v1 = temp_v0_2 < 0x121U;
        }
        var_a0 = 0;
        temp_v0_3 = (u32)((FIELD(arg2, u16, 0xF8) + 0x20) & 0xFFFF) < 0x181U;
        var_a1 |= var_v1;
        if (temp_v0_3) {
            temp_v0_2 = FIELD(arg2, u16, 0xFA) + 0x20;
            var_a0 = temp_v0_2 < 0x121U;
        }
        var_v1 = 0;
        temp_v0_3 = (u32)((FIELD(arg2, u16, 0xFC) + 0x20) & 0xFFFF) < 0x181U;
        temp_a0_2 = var_a1 | var_a0;
        var_a0 = temp_a0_2;
        if (temp_v0_3) {
            temp_v0_2 = FIELD(arg2, u16, 0xFE) + 0x20;
            var_v1 = temp_v0_2 < 0x121U;
        }
        if ((var_a0 | var_v1) != 0) {
            FIELD(var_s2, s32, -0x48) = FIELD(arg2, s32, 0xF0);
            FIELD(var_s2, s32, -0x30) = FIELD(arg2, s32, 0xF8);
            FIELD(var_s2, s32, -8) = FIELD(arg2, s32, 0xF4);
            FIELD(var_s2, s32, 0x10) = FIELD(arg2, s32, 0xFC);
            temp_v0_3 = (FIELD(arg2, s16, 0xF0) + FIELD(arg2, s16, 0xF4)) >> 1;
            FIELD(var_s2, s16, -0x14) = temp_v0_3;
            FIELD(var_s2, s16, -0x3C) = temp_v0_3;
            temp_v0_4 = (FIELD(arg2, s16, 0xF8) + FIELD(arg2, s16, 0xFC)) >> 1;
            FIELD(var_s2, s16, 4) = temp_v0_4;
            FIELD(var_s2, s16, -0x24) = temp_v0_4;
            temp_v0_5 = (FIELD(arg2, s16, 0xF2) + FIELD(arg2, s16, 0xF6)) >> 1;
            FIELD(var_s2, s16, -0x12) = temp_v0_5;
            FIELD(var_s2, s16, -0x3A) = temp_v0_5;
            temp_v0_6 = (FIELD(arg2, s16, 0xFA) + FIELD(arg2, s16, 0xFE)) >> 1;
            FIELD(var_s2, s16, 6) = temp_v0_6;
            FIELD(var_s2, s16, -0x22) = temp_v0_6;
            var_a0_2 = (s16)FIELD(arg2, u16, 0x74) % 3584;
            FIELD(arg2, s32, 0x90) = var_a0_2;
            if (var_a0_2 < 0) {
                var_a0_2 += 0xFF;
            }
            var_a0_2 >>= 8;
            FIELD(arg2, s32, 0x90) = var_a0_2;
            inner_v0 = sp38;
            if (inner_v0 != 0) {
                FIELD(arg2, s32, 0x90) = var_a0_2 + 0x10;
            }
            temp_a0_2 = 0x80;
            inner_v1 = FIELD(arg2, u16, 0x90);
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
            FIELD(var_s2, s8, -0x4A) = temp_a0_2;
            FIELD(var_s2, s8, -0x3E) = temp_a0_2;
            FIELD(var_s2, s8, -0xA) = temp_a0_2;
            FIELD(var_s2, s8, -0x16) = temp_a0_2;
            FIELD(var_s2, s8, -0x4B) = temp_a0_2;
            FIELD(var_s2, s8, -0x3F) = temp_a0_2;
            FIELD(var_s2, s8, -0xB) = temp_a0_2;
            FIELD(var_s2, s8, -0x17) = temp_a0_2;
            FIELD(var_s2, s8, -0x4C) = temp_a0_2;
            FIELD(var_s2, s8, -0x40) = temp_a0_2;
            FIELD(var_s2, s8, -0xC) = temp_a0_2;
            FIELD(var_s2, s8, -0x18) = temp_a0_2;
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
            FIELD(var_s2, s8, -0x32) = inner_v1;
            FIELD(var_s2, s8, -0x26) = inner_v1;
            FIELD(var_s2, s8, 0xE) = inner_v1;
            FIELD(var_s2, s8, 2) = inner_v1;
            FIELD(var_s2, s8, -0x33) = inner_v1;
            FIELD(var_s2, s8, -0x27) = inner_v1;
            FIELD(var_s2, s8, 0xD) = inner_v1;
            FIELD(var_s2, s8, 1) = inner_v1;
            FIELD(var_s2, s8, -0x34) = inner_v1;
            FIELD(var_s2, s8, -0x28) = inner_v1;
            FIELD(var_s2, s8, 0xC) = inner_v1;
            FIELD(var_s2, s8, 0) = inner_v1;
            inner_v1 = var_s7 & 1;
            ASM_KEEP(inner_v1);
            inner_v1 <<= 1;
            inner_v0 = (s32)(sp30 << 0x10) >> 0xE;
            inner_v1 += inner_v0;
            inner_v0 = inner_v1 << 1;
            inner_v0 += inner_v1;
            inner_v1 = FIELD(arg2, s32, 0x118);
            inner_v0 <<= 2;
            var_s4 = (TwelveByteEntry *)((u8 *)inner_v1 + inner_v0);
            var_s3 = (u8 *)var_s4 + 4;
            do {
                func_8006671C(var_s6);
                FIELD(arg2, volatile s32, 8) = FIELD(var_s3, u8, 4);
                temp_a1_2 = FIELD(arg2, volatile s32, 8);
                FIELD(arg2, volatile s32, 0xC) = FIELD(var_s3, u8, 5);
                temp_a0_2 = FIELD(arg2, volatile s32, 0xC);
                FIELD(arg2, volatile s32, 0x10) = FIELD(var_s3, u8, 6);
                inner_v1 = temp_a0_2;
                temp_a0_3 = FIELD(var_s3, u8, 7);
                temp_a0_2 <<= 8;
                FIELD(arg2, volatile s32, 0xC) = temp_a0_2;
                FIELD(arg2, volatile s32, 0x14) = temp_a0_3;
                temp_v0_3 = FIELD(arg2, volatile s32, 0x10);
                temp_a2 = FIELD(arg2, volatile s32, 0x14);
                temp_v0_3 += temp_a1_2;
                inner_v1 += temp_a2;
                inner_v1 <<= 8;
                FIELD(arg2, volatile s32, 0x14) = inner_v1;
                inner_v1 = temp_a1_2;
                ASM_KEEP(inner_v1);
                FIELD(arg2, volatile s32, 0x10) = temp_v0_3;
                inner_v0 = FIELD(var_s3, u16, 2);
                temp_a0_2 += inner_v1;
                inner_v0 <<= 0x10;
                temp_a0_2 |= inner_v0;
                FIELD(var_s0, s32, -0x25) = temp_a0_2;
                inner_v0 = FIELD(arg2, volatile s32, 0xC);
                temp_a0_2 = FIELD(arg2, volatile s32, 0x10);
                inner_v1 = FIELD(var_s3, s16, 0);
                inner_v0 += temp_a0_2;
                inner_v1 <<= 0x10;
                inner_v0 |= inner_v1;
                FIELD(var_s0, s32, -0x19) = inner_v0;
                inner_v0 = FIELD(arg2, volatile u16, 0x14);
                inner_v1 = FIELD(arg2, volatile u16, 8);
                ASM_KEEP(inner_v0);
                inner_v0 += inner_v1;
                FIELD(var_s0, volatile s16, -0xD) = inner_v0;
                inner_v1 = FIELD(arg2, volatile u16, 0x14);
                inner_v0 = FIELD(var_s0, volatile u8, -0x19);
                temp_a0_2 = FIELD(arg2, volatile u16, 0x10);
                ASM_KEEP(inner_v0);
                inner_v0 -= 1;
                inner_v1 += temp_a0_2;
                FIELD(var_s0, volatile s8, -0x19) = inner_v0;
                FIELD(var_s0, volatile s16, -1) = inner_v1;
                inner_v0 = FIELD(var_s0, volatile u8, -1);
                inner_v1 = FIELD(var_s0, volatile u8, -0xC);
                inner_v0 -= 1;
                inner_v1 -= 1;
                FIELD(var_s0, volatile s8, -1) = inner_v0;
                FIELD(var_s0, volatile u8, -0xC) = inner_v1;
                inner_v0 = FIELD(var_s0, volatile u8, 0);
                inner_v0 -= 1;
                FIELD(var_s0, volatile u8, 0) = inner_v0;
                inner_v1 = FIELD(arg2, s32, 0x118);
                temp_hi = (u32)(var_s4 - (TwelveByteEntry *)inner_v1) / 12;
                var_s2 += 0x34;
                var_s5 += 1;
                temp_a1_2 = (s32)var_s6;
                var_s3 += 0xC;
                var_s0 += 0x34;
                var_s4 += 1;
                func_8006658C(FIELD(arg2, s32, 0x20) + (temp_hi * 4),
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
