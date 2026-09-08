#include "common.h"

typedef struct S_8002222C_0 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_8002222C_0;   /* arena in func_8002222C */

typedef struct S_8002222C_1_pre {
    s32 unk_00;
    u8 pad_04[0x4];
} S_8002222C_1_pre;   /* the 0x8 bytes before var_s3 in func_8002222C, addressed as var_s3[-1] */

typedef struct S_8002222C_1 {
    u8 pad_00[0x18];
    s32 unk_18;
    s32 unk_1C;
} S_8002222C_1;   /* var_s3 in func_8002222C */

typedef struct S_8002222C_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
} S_8002222C_2;   /* temp_s0 in func_8002222C */

typedef struct S_8002222C_3 {
    s32 unk_00;
    s32 unk_04;
} S_8002222C_3;   /* scratch in func_8002222C */

typedef struct S_8002222C_4 {
    u16 unk_00;
    u16 unk_02;
} S_8002222C_4;   /* scratch100 in func_8002222C */

typedef struct S_8002222C_5 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} S_8002222C_5;   /* temp_a1_2 + temp_v0 in func_8002222C */

typedef struct S_8002222C_6 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} S_8002222C_6;   /* temp_a0 in func_8002222C */

typedef struct S_8002222C_7 {
    s32 unk_00;
} S_8002222C_7;   /* temp_s1 in func_8002222C */

typedef struct S_8002222C_8 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} S_8002222C_8;   /* temp_a1_2 in func_8002222C */



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
    register u8 *scratch100 ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *scratch180;
    register u8 *scratch_init ASM_REG("$30");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    u8 *scratch;
    u32 mask24;
    u32 mask_high;
    register s32 ret ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    var_s3 = arg0;
    basep = (u8 **)D_80083160;
    scratch_init = (u8 *)0x1F800000;
    ASM_KEEP_NV(scratch_init);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    scratch = scratch_init;
    scratch100 = scratch;
    ASM_KEEP_NV(scratch100);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    scratch100 = (u8 *)((u32)scratch100 | 0x100);
    scratch180 = scratch;
    ASM_KEEP_NV(scratch180);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    scratch180 = (u8 *)((u32)scratch180 | 0x180);
    mask24 = 0xFFFFFF;
    mask_high = 0xFF000000;
    do {
        func_80065770(var_s3 + 8, scratch, scratch100, scratch180,
                     scratch180, 2);
        {
            u8 *arena;
            s32 zero0;
            s32 zero_a1;
            s32 zero_a2;
            s32 zero_a3;
            u8 *next_s1;
            arena = *basep;
            ASM_KEEP(arena);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            zero0 = 0;
            ASM_KEEP(zero0);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            temp_s0 = ((S_8002222C_0 *)arena)->unk_8D0;
            ASM_KEEP(temp_s0);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            zero_a1 = zero0;
            ASM_KEEP(zero_a1);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            ((S_8002222C_0 *)arena)->unk_8D0 = temp_s0 + 0x14;
            arena = *basep;
            ASM_KEEP(arena);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            zero_a2 = zero0;
            ASM_KEEP(zero_a2);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            temp_s1 = ((S_8002222C_0 *)arena)->unk_8D0;
            ASM_KEEP(temp_s1);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            zero_a3 = zero0;
            ASM_KEEP(zero_a3);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            next_s1 = temp_s1 + 0xC;
            ASM_KEEP(next_s1);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            ((S_8002222C_0 *)arena)->unk_8D0 = next_s1;
            call_result = func_80066460(zero0, zero_a1, zero_a2, zero_a3);
        }
        {
            u8 *call_a0;
            s32 zero1;
            call_a0 = temp_s1;
            ASM_KEEP(call_a0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            zero1 = 0;
            ASM_KEEP(zero1);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            func_80067F20(call_a0, zero1, zero1, call_result & 0xFFFF, 0);
        }
        temp_v0 = ((S_8002222C_1 *)var_s3)->unk_18;
        ((S_8002222C_2 *)temp_s0)->unk_04 = temp_v0;
        temp_v0 = ((S_8002222C_1 *)var_s3)->unk_1C;
        ((S_8002222C_2 *)temp_s0)->unk_0C = temp_v0;
        func_800667D0(temp_s0);
        func_80066640(temp_s0, 1);
        temp_v0 = ((S_8002222C_3 *)scratch)->unk_00;
        ((S_8002222C_2 *)temp_s0)->unk_08 = temp_v0;
        temp_v0 = ((S_8002222C_3 *)scratch)->unk_04;
        ((S_8002222C_2 *)temp_s0)->unk_10 = temp_v0;
        {
            register s32 compare_a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 temp_v1;
            register u32 raw0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            raw0 = ((S_8002222C_4 *)scratch100)->unk_00;
            compare_a1 = raw0 << 0x10;
            temp_v1 = ((S_8002222C_4 *)scratch100)->unk_02 << 0x10;
            if (compare_a1 < temp_v1) {
                temp_v1 = compare_a1 >> 0x13;
            } else {
                temp_v1 >>= 0x13;
            }
            compare_a1 = temp_v1 * 4;
            ASM_KEEP(compare_a1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            temp_a1_2 = compare_a1;
        }
        temp_v0 = (s32)*basep;
        var_v1 = ((S_8002222C_2 *)temp_s0)->unk_00;
        temp_v0 = ((S_8002222C_5 *)(temp_a1_2 + temp_v0))->unk_B0;
        var_v1 &= mask_high;
        temp_v0 &= mask24;
        var_v1 |= temp_v0;
        ((S_8002222C_2 *)temp_s0)->unk_00 = var_v1;
        {
            register s32 base_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            base_a0 = (s32)*basep;
            temp_a0 = temp_a1_2 + base_a0;
        }
        temp_v0 = ((S_8002222C_6 *)temp_a0)->unk_B0;
        var_v1 = (u32)temp_s0 & mask24;
        temp_v0 &= mask_high;
        temp_v0 |= var_v1;
        ((S_8002222C_6 *)temp_a0)->unk_B0 = temp_v0;
        temp_v0 = (s32)*basep;
        var_v1 = ((S_8002222C_7 *)temp_s1)->unk_00;
        temp_v0 = ((S_8002222C_5 *)(temp_a1_2 + temp_v0))->unk_B0;
        var_v1 &= mask_high;
        temp_v0 &= mask24;
        var_v1 |= temp_v0;
        ((S_8002222C_7 *)temp_s1)->unk_00 = var_v1;
        temp_a1_2 += (s32)*basep;
        temp_v0 = ((S_8002222C_8 *)temp_a1_2)->unk_B0;
        var_v1 = (u32)temp_s1 & mask24;
        temp_v0 &= mask_high;
        temp_v0 |= var_v1;
        ((S_8002222C_8 *)temp_a1_2)->unk_B0 = temp_v0;
        temp_a0 = ((S_8002222C_1_pre *)var_s3)[-1].unk_00;
        var_s3 = temp_a0 + 0x20;
    } while (temp_a0 != 0);
    ret = 0;
    return ret;
}
