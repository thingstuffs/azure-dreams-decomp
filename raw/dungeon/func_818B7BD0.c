#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

typedef union {
    s64 value;
    s32 word[2];
} M2C_WIDE;

#if defined(__mips__) || defined(mips)
#define M2C_HIGH_WORD(product) ((product).word[0])
#else
#define M2C_HIGH_WORD(product) ((s32) ((u64) (product).value >> 32))
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void func_8002551C() __attribute__((noreturn));
void func_8003DB94(void *, void *, s32);
void *func_8003FC64();
M2C_UNK func_8004491C();
s32 func_80069EF8();
extern M2C_UNK D_800250E8;
extern M2C_UNK D_80025EE4;
extern M2C_UNK D_80045C34;

s32 func_818B7BD0(void *arg0, void *arg1) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3;
    register s32 temp_div_v1 ASM_REG("$3");
    register s32 temp_hi ASM_REG("$7");
    register s32 temp_quot ASM_REG("$4");
    s32 temp_ret;
    s32 temp_v1;
    s32 var_v0;
    register s32 result ASM_REG("$2");
    register void *temp_model ASM_REG("$5");
    register void *temp_tag ASM_REG("$2");
    register void *temp_s0 ASM_REG("$16");
    void *temp_v0;
    void *temp_v1_2;
    M2C_WIDE temp_product;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_tag = &D_800250E8;
        ASM_KEEP(temp_tag);
        temp_s0 = temp_v0 + 0x20;
        ASM_KEEP(temp_s0);
        M2C_FIELD(temp_v0, void **, 0x10) = temp_tag;
        M2C_FIELD(temp_v0, void **, 0x20) = arg0;
        M2C_FIELD(temp_s0, s16 *, 0xE) = 0;
        M2C_FIELD(temp_s0, s16 *, 0x10) = 0;
        temp_ret = func_80069EF8();
        temp_div_v1 = (s32) 0x92492493;
        temp_product.value = (s64) temp_ret * temp_div_v1;
        temp_div_v1 = temp_ret >> 31;
        temp_model = &D_80025EE4;
        ASM_KEEP(temp_model);
        temp_hi = M2C_HIGH_WORD(temp_product);
        ASM_KEEP(temp_hi);
        temp_quot = ((temp_hi + temp_ret) >> 2) - temp_div_v1;
        ASM_KEEP(temp_quot);
        M2C_FIELD(temp_s0, s16 *, 0x12) = (s16) (temp_ret - ((temp_quot << 3) - temp_quot));
        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) M2C_FIELD(arg0, u16 *, 0x12);
        M2C_FIELD(temp_s0, s32 *, 0x18) = (s32) M2C_FIELD(arg0, s32 *, 0x18);
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s0, u8 *, 0xE) = 0x80;
        M2C_FIELD(temp_s0, u8 *, 0xD) = 0x80;
        M2C_FIELD(temp_s0, u8 *, 0xC) = 0x80;
        M2C_FIELD(temp_s0, s16 *, 0x12) = 0x7E00;
        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0x100);
        func_8003DB94(temp_s0, temp_model, 0);
        var_v0 = func_80069EF8();
        temp_v1 = var_v0;
        if (temp_v1 < 0) {
            var_v0 = temp_v1 + 0xFFF;
        }
        M2C_FIELD(temp_s0, s16 *, 0x1A) = (s16) (temp_v1 - ((var_v0 >> 0xC) << 0xC));
        M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x400;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x400;
        func_8004491C(temp_v0, &D_80045C34);
        temp_v1_2 = M2C_FIELD(temp_v0, void **, 8);
        ASM_KEEP(temp_v1_2);
        result = (s32) temp_v0;
        ASM_KEEP(result);
        temp_a0 = M2C_FIELD(arg1, s32 *, 0);
        temp_a1 = M2C_FIELD(arg1, s32 *, 4);
        temp_a2 = M2C_FIELD(arg1, s32 *, 8);
        temp_a3 = M2C_FIELD(arg1, s32 *, 0xC);
        M2C_FIELD(temp_v1_2, s32 *, 0) = temp_a0;
        M2C_FIELD(temp_v1_2, s32 *, 4) = temp_a1;
        M2C_FIELD(temp_v1_2, s32 *, 8) = temp_a2;
        M2C_FIELD(temp_v1_2, s32 *, 0xC) = temp_a3;
        temp_a0 = M2C_FIELD(arg1, s32 *, 0x10);
        temp_a1 = M2C_FIELD(arg1, s32 *, 0x14);
        M2C_FIELD(temp_v1_2, s32 *, 0x10) = temp_a0;
        M2C_FIELD(temp_v1_2, s32 *, 0x14) = temp_a1;
        func_8002551C(temp_a0, temp_a1, temp_a2, temp_a3);
    }
    return 0;
}
