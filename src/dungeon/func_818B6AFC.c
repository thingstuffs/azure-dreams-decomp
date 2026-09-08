#include "common.h"
#include "m2c_compat.h"

typedef struct S_818B6AFC_0_pre {
    u16 unk_00;
} S_818B6AFC_0_pre;   /* the 0x2 bytes before arg0 in func_818B6AFC, addressed as arg0[-1] */

typedef struct S_818B6AFC_0 {
    void * unk_00;
    u8 pad_04[0x2];
    u16 unk_06;
    u16 unk_08;
    u8 pad_0A[0x2];
    u16 unk_0C;
    u16 unk_0E;
    void * unk_10;
} S_818B6AFC_0;   /* arg0 in func_818B6AFC */

typedef struct S_818B6AFC_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818B6AFC_1;   /* temp_v1 in func_818B6AFC */

typedef struct S_818B6AFC_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_818B6AFC_2;   /* temp_a0 in func_818B6AFC */

typedef struct S_818B6AFC_3 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_818B6AFC_3;   /* temp_t0 in func_818B6AFC */

typedef struct S_818B6AFC_4 {
    u8 pad_00[0xC];
    union { struct { s8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; s8 v; } at01; struct { u8 pad[0x2]; s8 v; } at02; } unk_0C;   /* overlapping accesses */
} S_818B6AFC_4;   /* arg2 in func_818B6AFC */

typedef struct S_818B6AFC_5 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_818B6AFC_5;   /* temp_a0_4 in func_818B6AFC */

typedef struct S_818B6AFC_6 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_818B6AFC_6;   /* temp_a0_7 in func_818B6AFC */

typedef struct S_818B6AFC_7 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_818B6AFC_7;   /* temp_a0_10 in func_818B6AFC */

typedef struct S_818B6AFC_8_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_818B6AFC_8_pre;   /* the 0x14 bytes before ((S_818B6AFC_0 *)arg0)->unk_10 in func_818B6AFC, addressed as ((S_818B6AFC_0 *)arg0)->unk_10[-1] */


M2C_UNK func_80024154();
M2C_UNK func_8002473C() __attribute__((noreturn));
M2C_UNK func_80024780() __attribute__((noreturn));
extern M2C_UNK D_800814A0;

#ifdef NON_MATCHING
#define M2C_READ_MUL_HI(dst, a, b) \
    do { (dst) = (s32) (((s64) (s32) (a) * (s64) (s32) (b)) >> 32); } while (0)
#define M2C_MUL_LO(a, b) ((s32) ((s64) (s32) (a) * (s64) (s32) (b)))
#else
register s32 implicit_lo ASM_REG("lo");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
#define M2C_READ_MUL_HI(dst, a, b) \
    do { \
        register s32 implicit_hi ASM_REG("hi"); \
        ASM_CLOBBER("hi"); \
        (dst) = implicit_hi; \
        \
        ASM_CLOBBER("hi"); \
    } while (0)
#define M2C_MUL_LO(a, b) \
    (implicit_lo = (s32) (a) * (s32) (b), implicit_lo)
#endif

void func_818B6AFC(void *in0, M2C_UNK arg1, void *arg2) {
    s32 temp_a0_2;
    s16 temp_a0_3;
    s32 temp_a0_5;
    s32 temp_a0_8;
    s16 temp_a0_9;
    s16 temp_v1_2;
    s16 temp_v1_4;
    register s32 var_a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 var_v0;
    s32 var_v1;
    register s32 temp_a0_6 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 temp_t1;
    register s32 temp_t2 ASM_REG("$10");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 temp_v1_3;
    s32 temp_v1_5;
    s32 packed_rem1;
    s32 remainder3;
    register s32 quotient3 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 packed3;
    s32 limit48;
    s32 delta48;
    s32 magic7;
    s32 dividend7;
    u16 raw1;
    u16 raw2;
    u16 raw3;
    register s32 product_result ASM_REG("$12");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s8 temp_v0;
    s8 temp_v0_2;
    s8 temp_v0_3;
    void *temp_a0;
    void *temp_a0_10;
    void *temp_a0_4;
    void *temp_a0_7;
    void *temp_t0;
    void *temp_v1;
    void *arg0;

    arg0 = in0;
    temp_v1 = ((S_818B6AFC_0 *)arg0)->unk_00;
    ((S_818B6AFC_1 *)temp_v1)->unk_14 = (u16) (((S_818B6AFC_1 *)temp_v1)->unk_14 + 1);
    ((S_818B6AFC_0 *)arg0)->unk_06 = (u16) (((S_818B6AFC_0 *)arg0)->unk_06 + 1);
    ((S_818B6AFC_0 *)arg0)->unk_08 = (u16) (((S_818B6AFC_0 *)arg0)->unk_08 + 1);
    ((S_818B6AFC_0 *)arg0)->unk_0C = (u16) (((S_818B6AFC_0 *)arg0)->unk_0C + 0x80);
    ((S_818B6AFC_0 *)arg0)->unk_0E = (u16) (((S_818B6AFC_0 *)arg0)->unk_0E + 0x80);
    temp_v1_2 = (s16) ((S_818B6AFC_0 *)arg0)->unk_06;
    if (temp_v1_2 < 8) {
        temp_a0 = ((S_818B6AFC_0 *)arg0)->unk_10;
        ((S_818B6AFC_2 *)temp_a0)->unk_1C = (s32) (((S_818B6AFC_2 *)temp_a0)->unk_1C | 0x10000000);
        raw1 = ((S_818B6AFC_0 *)arg0)->unk_08;
        dividend7 = (s16) raw1;
        magic7 = (s32) 0x92490000;
        magic7 = (s32) ((u32) magic7 | 0x2493);
#ifndef NON_MATCHING
        implicit_lo = dividend7 * magic7;
#endif
        temp_t0 = ((S_818B6AFC_8_pre *)(((S_818B6AFC_0 *)arg0)->unk_10))[-1].unk_00;
        var_a1 = (s32) (s16) raw1 >> 31;
        M2C_READ_MUL_HI(product_result, dividend7, magic7);
        quotient3 = ((product_result + dividend7) >> 2) - var_a1;
        ASM_KEEP_NV(quotient3);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        dividend7 = dividend7 - (quotient3 * 7);
        dividend7 = dividend7 + 1;
        packed_rem1 = (s32) ((u32) dividend7 << 16);
        temp_a0_2 = packed_rem1 >> 16;
        var_a1 = temp_a0_2;
        if (temp_a0_2 < 0) {
            var_a1 = temp_a0_2 + 3;
        }
        temp_t1 = var_a1 >> 2;
        product_result = M2C_MUL_LO(temp_t1, (s16) ((S_818B6AFC_0 *)arg0)->unk_06 << 3);
        temp_v1_3 = (temp_a0_2 + (s32) ((u32) packed_rem1 >> 31)) >> 1;
        ((S_818B6AFC_3 *)temp_t0)->unk_0C = (s8) (product_result - 0x80);
        ASM_KEEP(product_result);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        temp_a0_3 = (s16) temp_v1_3 % 2;
        packed_rem1 = (s32) ((u32) (temp_a0_2 - (temp_v1_3 * 2)) << 16);
        product_result = M2C_MUL_LO(temp_a0_3, (s16) ((S_818B6AFC_0 *)arg0)->unk_06 << 3);
        ((S_818B6AFC_3 *)temp_t0)->unk_0D = (s8) (product_result - 0x80);
        ASM_KEEP(product_result);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        temp_v1_4 = packed_rem1 >> 16;
        product_result = M2C_MUL_LO(temp_v1_4, (s16) ((S_818B6AFC_0 *)arg0)->unk_06 << 3);
        ((S_818B6AFC_3 *)temp_t0)->unk_0E = (s8) (product_result - 0x80);
        ASM_KEEP(product_result);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        product_result = M2C_MUL_LO(temp_t1, ((s16) ((S_818B6AFC_0 *)arg0)->unk_06 * 3) << 3);
        ((S_818B6AFC_4 *)arg2)->unk_0C.at00.v = (s8) product_result;
        product_result = M2C_MUL_LO(temp_a0_3, ((s16) ((S_818B6AFC_0 *)arg0)->unk_06 * 3) << 3);
        ((S_818B6AFC_4 *)arg2)->unk_0C.at01.v = (s8) product_result;
#ifdef NON_MATCHING
        ((S_818B6AFC_4 *)arg2)->unk_0C.at02.v = (s8) (temp_v1_4 * ((((s16) ((S_818B6AFC_0 *)arg0)->unk_06 * 3)) << 3));
#else
        implicit_lo = temp_v1_4 * (((s16) ((S_818B6AFC_0 *)arg0)->unk_06 * 3) << 3);
#endif
        func_8002473C(temp_a0_3, temp_v1_4, temp_a0_2, arg0);
        return;
    }
    if (temp_v1_2 < 0x28) {
        temp_a0_4 = ((S_818B6AFC_0 *)arg0)->unk_10;
        ((S_818B6AFC_5 *)temp_a0_4)->unk_1C = (s32) (((S_818B6AFC_5 *)temp_a0_4)->unk_1C | 0x10000000);
        raw2 = ((S_818B6AFC_0 *)arg0)->unk_08;
        dividend7 = (s16) raw2;
        magic7 = (s32) 0x92490000;
        magic7 = (s32) ((u32) magic7 | 0x2493);
#ifndef NON_MATCHING
        implicit_lo = dividend7 * magic7;
#endif
        temp_t0 = ((S_818B6AFC_8_pre *)(((S_818B6AFC_0 *)arg0)->unk_10))[-1].unk_00;
        var_a1 = (s32) (s16) raw2 >> 31;
        M2C_READ_MUL_HI(product_result, dividend7, magic7);
        quotient3 = ((product_result + dividend7) >> 2) - var_a1;
        ASM_KEEP_NV(quotient3);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        dividend7 = dividend7 - (quotient3 * 7);
        dividend7 = dividend7 + 1;
        dividend7 = (s32) ((u32) dividend7 << 16);
        temp_a0_5 = dividend7 >> 16;
        var_v1 = temp_a0_5;
        if (temp_a0_5 < 0) {
            var_v1 = temp_a0_5 + 3;
        }
        temp_v0 = (var_v1 >> 2) * 0xC0;
        temp_a0_6 = (temp_a0_5 + (s32) ((u32) dividend7 >> 31)) >> 1;
        ((S_818B6AFC_4 *)arg2)->unk_0C.at00.v = temp_v0;
        ((S_818B6AFC_3 *)temp_t0)->unk_0C = temp_v0;
        temp_v0_2 = ((s16) temp_a0_6 % 2) * 0xC0;
        temp_a0_6 = (s16) (temp_a0_5 - (temp_a0_6 * 2));
        ((S_818B6AFC_4 *)arg2)->unk_0C.at01.v = temp_v0_2;
        ((S_818B6AFC_3 *)temp_t0)->unk_0D = temp_v0_2;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        temp_v0_3 = temp_a0_6 * 0xC0;
        ((S_818B6AFC_4 *)arg2)->unk_0C.at02.v = temp_v0_3;
        ((S_818B6AFC_3 *)temp_t0)->unk_0E = temp_v0_3;
        func_80024154(((S_818B6AFC_0 *)arg0)->unk_00, arg1, ((S_818B6AFC_4 *)arg2)->unk_0C.at00u.v, arg0);
        func_80024780();
        return;
    }
    if (temp_v1_2 < 0x30) {
        temp_a0_7 = ((S_818B6AFC_0 *)arg0)->unk_10;
        ((S_818B6AFC_6 *)temp_a0_7)->unk_1C = (s32) (((S_818B6AFC_6 *)temp_a0_7)->unk_1C | 0x10000000);
        raw3 = ((S_818B6AFC_0 *)arg0)->unk_08;
        remainder3 = (s16) raw3;
        magic7 = (s32) 0x92490000;
        magic7 = (s32) ((u32) magic7 | 0x2493);
#ifndef NON_MATCHING
        implicit_lo = remainder3 * magic7;
#endif
        temp_t0 = ((S_818B6AFC_8_pre *)(((S_818B6AFC_0 *)arg0)->unk_10))[-1].unk_00;
        var_a1 = (s32) (s16) raw3 >> 31;
        M2C_READ_MUL_HI(product_result, remainder3, magic7);
        quotient3 = ((product_result + remainder3) >> 2) - var_a1;
        ASM_KEEP_NV(quotient3);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        remainder3 = remainder3 - (quotient3 * 7);
        remainder3 = remainder3 + 1;
        packed3 = (s32) ((u32) remainder3 << 16);
        temp_a0_8 = packed3 >> 16;
        var_v0 = temp_a0_8;
        if (temp_a0_8 < 0) {
            var_v0 = temp_a0_8 + 3;
        }
        temp_t2 = var_v0 >> 2;
        temp_v1_5 = (temp_a0_8 + (s32) ((u32) packed3 >> 31)) >> 1;
        var_v0 = (s16) ((S_818B6AFC_0 *)arg0)->unk_06;
        ASM_KEEP_NV(var_v0);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        limit48 = 0x30;
        ASM_KEEP_NV(limit48);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        var_v0 = limit48 - var_v0;
        product_result = M2C_MUL_LO(temp_t2, var_v0 << 3);
        ((S_818B6AFC_3 *)temp_t0)->unk_0C = (s8) (product_result - 0x80);
        ASM_KEEP(product_result);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        temp_a0_9 = (s16) temp_v1_5 % 2;
        packed_rem1 = (s32) ((u32) (temp_a0_8 - (temp_v1_5 * 2)) << 16);
        product_result = M2C_MUL_LO(temp_a0_9, (limit48 - (s16) ((S_818B6AFC_0 *)arg0)->unk_06) << 3);
        ((S_818B6AFC_3 *)temp_t0)->unk_0D = (s8) (product_result - 0x80);
        ASM_KEEP(product_result);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        temp_t1 = packed_rem1 >> 16;
        product_result = M2C_MUL_LO(temp_t1, (limit48 - (s16) ((S_818B6AFC_0 *)arg0)->unk_06) << 3);
        ((S_818B6AFC_3 *)temp_t0)->unk_0E = (s8) (product_result - 0x80);
        ASM_KEEP(product_result);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        delta48 = (s16) ((S_818B6AFC_0 *)arg0)->unk_06;
        delta48 = limit48 - delta48;
        product_result = M2C_MUL_LO(temp_t2, (delta48 * 3) << 3);
        ((S_818B6AFC_4 *)arg2)->unk_0C.at00.v = (s8) product_result;
        delta48 = (s16) ((S_818B6AFC_0 *)arg0)->unk_06;
        delta48 = limit48 - delta48;
        product_result = M2C_MUL_LO(temp_a0_9, (delta48 * 3) << 3);
        ((S_818B6AFC_4 *)arg2)->unk_0C.at01.v = (s8) product_result;
        delta48 = (s16) ((S_818B6AFC_0 *)arg0)->unk_06;
        delta48 = limit48 - delta48;
        product_result = M2C_MUL_LO(temp_t1, (delta48 * 3) << 3);
        ((S_818B6AFC_4 *)arg2)->unk_0C.at02.v = (s8) product_result;
        func_80024780(temp_a0_9, temp_a0_8, limit48, arg0);
        return;
    }
    temp_a0_10 = ((S_818B6AFC_0 *)arg0)->unk_10;
    ((S_818B6AFC_7 *)temp_a0_10)->unk_1C = (s32) (((S_818B6AFC_7 *)temp_a0_10)->unk_1C & 0xEFFFFFFF);
    (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_818B6AFC_0_pre *)arg0)[-1].unk_00 | 0x8000);
    D_800814A0 = D_800814A0 | 0x8000;
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
}
