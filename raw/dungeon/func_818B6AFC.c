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

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80024154();
M2C_UNK func_8002473C() __attribute__((noreturn));
M2C_UNK func_80024780() __attribute__((noreturn));
extern M2C_UNK D_800814A0;

#ifdef NON_MATCHING
#define M2C_READ_MUL_HI(dst, a, b) \
    do { (dst) = (s32) (((s64) (s32) (a) * (s64) (s32) (b)) >> 32); } while (0)
#define M2C_MUL_LO(a, b) ((s32) ((s64) (s32) (a) * (s64) (s32) (b)))
#else
register s32 implicit_lo ASM_REG("lo");
#define M2C_READ_MUL_HI(dst, a, b) \
    do { \
        register s32 implicit_hi ASM_REG("hi"); \
        ASM_CLOBBER("hi"); \
        (dst) = implicit_hi; \
        ASM_KEEP_NV(dst); \
        ASM_CLOBBER("hi"); \
    } while (0)
#define M2C_MUL_LO(a, b) \
    (implicit_lo = (s32) (a) * (s32) (b), implicit_lo)
#endif

void func_818B6AFC(void *in0, M2C_UNK arg1, void *arg2) {
    register s32 temp_a0_2 ASM_REG("$6");
    register s16 temp_a0_3 ASM_REG("$4");
    register s32 temp_a0_5 ASM_REG("$5");
    register s32 temp_a0_8 ASM_REG("$5");
    s16 temp_a0_9;
    s16 temp_v1_2;
    s16 temp_v1_4;
    register s32 var_a1 ASM_REG("$5");
    register s32 var_v0 ASM_REG("$2");
    s32 var_v1;
    register s32 temp_a0_6 ASM_REG("$4");
    register s32 temp_t1 ASM_REG("$9");
    register s32 temp_t2 ASM_REG("$10");
    register s32 temp_v1_3 ASM_REG("$3");
    register s32 temp_v1_5 ASM_REG("$3");
    register s32 packed_rem1 ASM_REG("$3");
    register s32 remainder3 ASM_REG("$4");
    register s32 quotient3 ASM_REG("$3");
    register s32 packed3 ASM_REG("$3");
    register s32 limit48 ASM_REG("$6");
    register s32 delta48 ASM_REG("$3");
    register s32 magic7 ASM_REG("$6");
    register s32 dividend7 ASM_REG("$4");
    register u16 raw1 ASM_REG("$5");
    register u16 raw2 ASM_REG("$5");
    register u16 raw3 ASM_REG("$5");
    register s32 product_result ASM_REG("$12");
    s8 temp_v0;
    s8 temp_v0_2;
    s8 temp_v0_3;
    void *temp_a0;
    void *temp_a0_10;
    void *temp_a0_4;
    void *temp_a0_7;
    register void *temp_t0 ASM_REG("$8");
    void *temp_v1;
    register void *arg0 ASM_REG("$7");

    arg0 = in0;
    ASM_KEEP_NV(arg0);
    temp_v1 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_v1, u16 *, 0x14) = (u16) (M2C_FIELD(temp_v1, u16 *, 0x14) + 1);
    M2C_FIELD(arg0, u16 *, 6) = (u16) (M2C_FIELD(arg0, u16 *, 6) + 1);
    M2C_FIELD(arg0, u16 *, 8) = (u16) (M2C_FIELD(arg0, u16 *, 8) + 1);
    M2C_FIELD(arg0, u16 *, 0xC) = (u16) (M2C_FIELD(arg0, u16 *, 0xC) + 0x80);
    M2C_FIELD(arg0, u16 *, 0xE) = (u16) (M2C_FIELD(arg0, u16 *, 0xE) + 0x80);
    temp_v1_2 = (s16) M2C_FIELD(arg0, u16 *, 6);
    if (temp_v1_2 < 8) {
        temp_a0 = M2C_FIELD(arg0, void **, 0x10);
        ASM_KEEP_NV(temp_a0);
        M2C_FIELD(temp_a0, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_a0, s32 *, 0x1C) | 0x10000000);
        raw1 = M2C_FIELD(arg0, u16 *, 8);
        dividend7 = (s16) raw1;
        magic7 = (s32) 0x92490000;
        ASM_KEEP_DEP_NV(magic7, raw1);
        magic7 = (s32) ((u32) magic7 | 0x2493);
        ASM_KEEP_NV(magic7);
#ifndef NON_MATCHING
        implicit_lo = dividend7 * magic7;
#endif
        temp_t0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), void **, -0x14);
        var_a1 = (s32) (s16) raw1 >> 31;
        ASM_KEEP_NV(var_a1);
        M2C_READ_MUL_HI(product_result, dividend7, magic7);
        quotient3 = ((product_result + dividend7) >> 2) - var_a1;
        ASM_KEEP_NV(quotient3);
        dividend7 = dividend7 - (quotient3 * 7);
        dividend7 = dividend7 + 1;
        packed_rem1 = (s32) ((u32) dividend7 << 16);
        ASM_KEEP_NV(packed_rem1);
        temp_a0_2 = packed_rem1 >> 16;
        ASM_KEEP_NV(temp_a0_2);
        var_a1 = temp_a0_2;
        if (temp_a0_2 < 0) {
            var_a1 = temp_a0_2 + 3;
        }
        ASM_KEEP_NV(var_a1);
        temp_t1 = var_a1 >> 2;
        product_result = M2C_MUL_LO(temp_t1, (s16) M2C_FIELD(arg0, u16 *, 6) << 3);
        temp_v1_3 = (temp_a0_2 + (s32) ((u32) packed_rem1 >> 31)) >> 1;
        ASM_KEEP_NV(temp_v1_3);
        M2C_FIELD(temp_t0, s8 *, 0xC) = (s8) (product_result - 0x80);
        ASM_KEEP(product_result);
        temp_a0_3 = (s16) temp_v1_3 % 2;
        ASM_KEEP_NV(temp_a0_3);
        packed_rem1 = (s32) ((u32) (temp_a0_2 - (temp_v1_3 * 2)) << 16);
        ASM_KEEP_NV(packed_rem1);
        product_result = M2C_MUL_LO(temp_a0_3, (s16) M2C_FIELD(arg0, u16 *, 6) << 3);
        M2C_FIELD(temp_t0, s8 *, 0xD) = (s8) (product_result - 0x80);
        ASM_KEEP(product_result);
        temp_v1_4 = packed_rem1 >> 16;
        product_result = M2C_MUL_LO(temp_v1_4, (s16) M2C_FIELD(arg0, u16 *, 6) << 3);
        M2C_FIELD(temp_t0, s8 *, 0xE) = (s8) (product_result - 0x80);
        ASM_KEEP(product_result);
        product_result = M2C_MUL_LO(temp_t1, ((s16) M2C_FIELD(arg0, u16 *, 6) * 3) << 3);
        M2C_FIELD(arg2, s8 *, 0xC) = (s8) product_result;
        ASM_KEEP(product_result);
        product_result = M2C_MUL_LO(temp_a0_3, ((s16) M2C_FIELD(arg0, u16 *, 6) * 3) << 3);
        M2C_FIELD(arg2, s8 *, 0xD) = (s8) product_result;
        ASM_KEEP(product_result);
#ifdef NON_MATCHING
        M2C_FIELD(arg2, s8 *, 0xE) = (s8) (temp_v1_4 * ((((s16) M2C_FIELD(arg0, u16 *, 6) * 3)) << 3));
#else
        implicit_lo = temp_v1_4 * (((s16) M2C_FIELD(arg0, u16 *, 6) * 3) << 3);
#endif
        func_8002473C(temp_a0_3, temp_v1_4, temp_a0_2, arg0);
        return;
    }
    if (temp_v1_2 < 0x28) {
        temp_a0_4 = M2C_FIELD(arg0, void **, 0x10);
        M2C_FIELD(temp_a0_4, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_a0_4, s32 *, 0x1C) | 0x10000000);
        raw2 = M2C_FIELD(arg0, u16 *, 8);
        dividend7 = (s16) raw2;
        magic7 = (s32) 0x92490000;
        ASM_KEEP_DEP_NV(magic7, raw2);
        magic7 = (s32) ((u32) magic7 | 0x2493);
        ASM_KEEP_NV(magic7);
#ifndef NON_MATCHING
        implicit_lo = dividend7 * magic7;
#endif
        temp_t0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), void **, -0x14);
        var_a1 = (s32) (s16) raw2 >> 31;
        ASM_KEEP_NV(var_a1);
        M2C_READ_MUL_HI(product_result, dividend7, magic7);
        quotient3 = ((product_result + dividend7) >> 2) - var_a1;
        ASM_KEEP_NV(quotient3);
        dividend7 = dividend7 - (quotient3 * 7);
        dividend7 = dividend7 + 1;
        dividend7 = (s32) ((u32) dividend7 << 16);
        ASM_KEEP_NV(dividend7);
        temp_a0_5 = dividend7 >> 16;
        ASM_KEEP_NV(temp_a0_5);
        var_v1 = temp_a0_5;
        if (temp_a0_5 < 0) {
            var_v1 = temp_a0_5 + 3;
        }
        temp_v0 = (var_v1 >> 2) * 0xC0;
        ASM_SCHED_BARRIER();
        temp_a0_6 = (temp_a0_5 + (s32) ((u32) dividend7 >> 31)) >> 1;
        ASM_KEEP(temp_a0_6);
        M2C_FIELD(arg2, s8 *, 0xC) = temp_v0;
        M2C_FIELD(temp_t0, s8 *, 0xC) = temp_v0;
        ASM_SCHED_BARRIER();
        temp_v0_2 = ((s16) temp_a0_6 % 2) * 0xC0;
        ASM_SCHED_BARRIER();
        temp_a0_6 = (s16) (temp_a0_5 - (temp_a0_6 * 2));
        ASM_KEEP(temp_a0_6);
        M2C_FIELD(arg2, s8 *, 0xD) = temp_v0_2;
        M2C_FIELD(temp_t0, s8 *, 0xD) = temp_v0_2;
        ASM_SCHED_BARRIER();
        temp_v0_3 = temp_a0_6 * 0xC0;
        M2C_FIELD(arg2, s8 *, 0xE) = temp_v0_3;
        M2C_FIELD(temp_t0, s8 *, 0xE) = temp_v0_3;
        func_80024154(M2C_FIELD(arg0, void **, 0), arg1, M2C_FIELD(arg2, s32 *, 0xC), arg0);
        func_80024780();
        return;
    }
    if (temp_v1_2 < 0x30) {
        temp_a0_7 = M2C_FIELD(arg0, void **, 0x10);
        M2C_FIELD(temp_a0_7, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_a0_7, s32 *, 0x1C) | 0x10000000);
        raw3 = M2C_FIELD(arg0, u16 *, 8);
        remainder3 = (s16) raw3;
        magic7 = (s32) 0x92490000;
        ASM_KEEP_DEP_NV(magic7, raw3);
        magic7 = (s32) ((u32) magic7 | 0x2493);
        ASM_KEEP_NV(magic7);
#ifndef NON_MATCHING
        implicit_lo = remainder3 * magic7;
#endif
        temp_t0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), void **, -0x14);
        var_a1 = (s32) (s16) raw3 >> 31;
        ASM_KEEP_NV(var_a1);
        M2C_READ_MUL_HI(product_result, remainder3, magic7);
        quotient3 = ((product_result + remainder3) >> 2) - var_a1;
        ASM_KEEP_NV(quotient3);
        remainder3 = remainder3 - (quotient3 * 7);
        ASM_KEEP_NV(remainder3);
        remainder3 = remainder3 + 1;
        ASM_KEEP_NV(remainder3);
        packed3 = (s32) ((u32) remainder3 << 16);
        ASM_KEEP_NV(packed3);
        temp_a0_8 = packed3 >> 16;
        ASM_KEEP_NV(temp_a0_8);
        var_v0 = temp_a0_8;
        if (temp_a0_8 < 0) {
            var_v0 = temp_a0_8 + 3;
        }
        ASM_KEEP_NV(var_v0);
        temp_t2 = var_v0 >> 2;
        ASM_KEEP_NV(temp_t2);
        temp_v1_5 = (temp_a0_8 + (s32) ((u32) packed3 >> 31)) >> 1;
        ASM_KEEP_NV(temp_v1_5);
        var_v0 = (s16) M2C_FIELD(arg0, u16 *, 6);
        ASM_KEEP_NV(var_v0);
        limit48 = 0x30;
        ASM_KEEP_NV(limit48);
        var_v0 = limit48 - var_v0;
        ASM_KEEP_NV(var_v0);
        product_result = M2C_MUL_LO(temp_t2, var_v0 << 3);
        M2C_FIELD(temp_t0, s8 *, 0xC) = (s8) (product_result - 0x80);
        ASM_KEEP(product_result);
        temp_a0_9 = (s16) temp_v1_5 % 2;
        packed_rem1 = (s32) ((u32) (temp_a0_8 - (temp_v1_5 * 2)) << 16);
        ASM_KEEP_NV(packed_rem1);
        product_result = M2C_MUL_LO(temp_a0_9, (limit48 - (s16) M2C_FIELD(arg0, u16 *, 6)) << 3);
        M2C_FIELD(temp_t0, s8 *, 0xD) = (s8) (product_result - 0x80);
        ASM_KEEP(product_result);
        temp_t1 = packed_rem1 >> 16;
        product_result = M2C_MUL_LO(temp_t1, (limit48 - (s16) M2C_FIELD(arg0, u16 *, 6)) << 3);
        M2C_FIELD(temp_t0, s8 *, 0xE) = (s8) (product_result - 0x80);
        ASM_KEEP(product_result);
        delta48 = (s16) M2C_FIELD(arg0, u16 *, 6);
        ASM_KEEP_NV(delta48);
        delta48 = limit48 - delta48;
        ASM_KEEP_NV(delta48);
        product_result = M2C_MUL_LO(temp_t2, (delta48 * 3) << 3);
        M2C_FIELD(arg2, s8 *, 0xC) = (s8) product_result;
        ASM_KEEP(product_result);
        delta48 = (s16) M2C_FIELD(arg0, u16 *, 6);
        ASM_KEEP_NV(delta48);
        delta48 = limit48 - delta48;
        ASM_KEEP_NV(delta48);
        product_result = M2C_MUL_LO(temp_a0_9, (delta48 * 3) << 3);
        M2C_FIELD(arg2, s8 *, 0xD) = (s8) product_result;
        ASM_KEEP(product_result);
        delta48 = (s16) M2C_FIELD(arg0, u16 *, 6);
        ASM_KEEP_NV(delta48);
        delta48 = limit48 - delta48;
        ASM_KEEP_NV(delta48);
        product_result = M2C_MUL_LO(temp_t1, (delta48 * 3) << 3);
        ASM_KEEP_NV(product_result);
        M2C_FIELD(arg2, s8 *, 0xE) = (s8) product_result;
        func_80024780(temp_a0_9, temp_a0_8, limit48, arg0);
        return;
    }
    temp_a0_10 = M2C_FIELD(arg0, void **, 0x10);
    M2C_FIELD(temp_a0_10, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_a0_10, s32 *, 0x1C) & 0xEFFFFFFF);
    M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
    D_800814A0 = D_800814A0 | 0x8000;
    ASM_MEM_BARRIER();
}
