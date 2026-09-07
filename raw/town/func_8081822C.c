#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80065770(void *, void *, void *, void *, void *, s32);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80066640(void *, s32);
extern void func_800667D0(void *);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern u8 D_80083160[];
extern u8 D_1F800000[];

s32 func_8002222C(void *arg0) {
    u8 *temp_s0;
    u8 *temp_s1;
    s32 temp_a0;
    s32 temp_a1_2;
    s32 temp_v0;
    s32 var_v1;
    s32 call_result;
    u8 *var_s3;
    u8 **basep;
    register u8 *scratch100 ASM_REG("$22");
    register u8 *scratch180 ASM_REG("$23");
    register u8 *scratch_init ASM_REG("$30");
    u8 *scratch;
    u32 mask24;
    u32 mask_high;
    register s32 ret ASM_REG("$2");

    var_s3 = arg0;
    basep = (u8 **)D_80083160;
    scratch_init = (u8 *)0x1F800000;
    ASM_KEEP_NV(scratch_init);
    scratch = scratch_init;
    scratch100 = scratch;
    ASM_KEEP_NV(scratch100);
    scratch100 = (u8 *)((u32)scratch100 | 0x100);
    ASM_KEEP_NV(scratch100);
    scratch180 = scratch;
    ASM_KEEP_NV(scratch180);
    scratch180 = (u8 *)((u32)scratch180 | 0x180);
    ASM_KEEP_NV(scratch180);
    mask24 = 0xFFFFFF;
    mask_high = 0xFF000000;
    do {
        func_80065770(var_s3 + 8, scratch, scratch100, scratch180,
                     scratch180, 2);
        {
            register u8 *arena ASM_REG("$3");
            register s32 zero0 ASM_REG("$4");
            register s32 zero_a1 ASM_REG("$5");
            register s32 zero_a2 ASM_REG("$6");
            register s32 zero_a3 ASM_REG("$7");
            register u8 *next_s1 ASM_REG("$2");
            arena = *basep;
            ASM_KEEP(arena);
            zero0 = 0;
            ASM_KEEP(zero0);
            temp_s0 = FIELD(arena, u8 *, 0x8D0);
            ASM_KEEP(temp_s0);
            zero_a1 = zero0;
            ASM_KEEP(zero_a1);
            FIELD(arena, u8 *, 0x8D0) = temp_s0 + 0x14;
            arena = *basep;
            ASM_KEEP(arena);
            zero_a2 = zero0;
            ASM_KEEP(zero_a2);
            temp_s1 = FIELD(arena, u8 *, 0x8D0);
            ASM_KEEP(temp_s1);
            zero_a3 = zero0;
            ASM_KEEP(zero_a3);
            next_s1 = temp_s1 + 0xC;
            ASM_KEEP(next_s1);
            FIELD(arena, u8 *, 0x8D0) = next_s1;
            call_result = func_80066460(zero0, zero_a1, zero_a2, zero_a3);
        }
        {
            register u8 *call_a0 ASM_REG("$4");
            register s32 zero1 ASM_REG("$5");
            call_a0 = temp_s1;
            ASM_KEEP(call_a0);
            zero1 = 0;
            ASM_KEEP(zero1);
            func_80067F20(call_a0, zero1, zero1, call_result & 0xFFFF, 0);
        }
        temp_v0 = FIELD(var_s3, s32, 0x18);
        FIELD(temp_s0, s32, 4) = temp_v0;
        temp_v0 = FIELD(var_s3, s32, 0x1C);
        FIELD(temp_s0, s32, 0xC) = temp_v0;
        func_800667D0(temp_s0);
        func_80066640(temp_s0, 1);
        temp_v0 = FIELD(scratch, s32, 0);
        FIELD(temp_s0, s32, 8) = temp_v0;
        temp_v0 = FIELD(scratch, s32, 4);
        FIELD(temp_s0, s32, 0x10) = temp_v0;
        {
            register s32 compare_a1 ASM_REG("$5");
            register s32 temp_v1 ASM_REG("$3");
            register u32 raw0 ASM_REG("$2");
            raw0 = FIELD(scratch100, u16, 0);
            ASM_KEEP(raw0);
            compare_a1 = raw0 << 0x10;
            temp_v1 = FIELD(scratch100, u16, 2) << 0x10;
            if (compare_a1 < temp_v1) {
                temp_v1 = compare_a1 >> 0x13;
            } else {
                temp_v1 >>= 0x13;
            }
            ASM_KEEP(temp_v1);
            compare_a1 = temp_v1 * 4;
            ASM_KEEP(compare_a1);
            temp_a1_2 = compare_a1;
        }
        temp_v0 = (s32)*basep;
        var_v1 = FIELD(temp_s0, s32, 0);
        temp_v0 = FIELD(temp_a1_2 + temp_v0, s32, 0xB0);
        var_v1 &= mask_high;
        temp_v0 &= mask24;
        var_v1 |= temp_v0;
        FIELD(temp_s0, s32, 0) = var_v1;
        {
            register s32 base_a0 ASM_REG("$4");
            base_a0 = (s32)*basep;
            ASM_KEEP_NV(base_a0);
            temp_a0 = temp_a1_2 + base_a0;
        }
        temp_v0 = FIELD(temp_a0, s32, 0xB0);
        var_v1 = (u32)temp_s0 & mask24;
        temp_v0 &= mask_high;
        temp_v0 |= var_v1;
        FIELD(temp_a0, s32, 0xB0) = temp_v0;
        temp_v0 = (s32)*basep;
        var_v1 = FIELD(temp_s1, s32, 0);
        temp_v0 = FIELD(temp_a1_2 + temp_v0, s32, 0xB0);
        var_v1 &= mask_high;
        temp_v0 &= mask24;
        var_v1 |= temp_v0;
        FIELD(temp_s1, s32, 0) = var_v1;
        temp_a1_2 += (s32)*basep;
        temp_v0 = FIELD(temp_a1_2, s32, 0xB0);
        var_v1 = (u32)temp_s1 & mask24;
        temp_v0 &= mask_high;
        temp_v0 |= var_v1;
        FIELD(temp_a1_2, s32, 0xB0) = temp_v0;
        temp_a0 = FIELD(var_s3, s32, -8);
        var_s3 = temp_a0 + 0x20;
    } while (temp_a0 != 0);
    ret = 0;
    ASM_KEEP(ret);
    return ret;
}
