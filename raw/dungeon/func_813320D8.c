/* cfail-repair: true-name warm-start */
#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

typedef struct {
    u8 bytes[32];
} Copy32;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_8003DB94();
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern M2C_UNK D_80045340[3];
extern M2C_UNK D_800DEAE0[3];
extern Copy32 D_801648DC;
extern M2C_UNK D_80168C88[3];
extern u8 D_80175DD8[96];

void func_801690D8(void *arg0_in, void *arg1, s32 arg2, s32 arg3) {
    s32 sp10[8];
    s32 var_s1;
    s32 var_s6;
    s32 temp_a2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a0_4;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a1_3;
    s32 var_a1_4;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a0_3;
    void *temp_s0;
    void *temp_v0;
    void *arg0_work;
    s32 *stack_base;
    u16 *coeff_ptr;
    u8 *table_base;
    void *arg1_reg;

    arg1_reg = arg1;
    arg0_work = arg0_in;
    *(Copy32 *)sp10 = D_801648DC;
    var_s1 = 0;
    stack_base = sp10;
    var_s6 = 0xFFFF;
    table_base = D_80175DD8;
    do {
        temp_v0 = func_8003FC64(0x12);
        temp_s0 = temp_v0 + 0x20;
        if (temp_v0 != NULL) {
            M2C_FIELD(temp_s0, u16 *, 0x18) = 0xEU;
            if ((var_s1 == 0) || (var_s1 == 7)) {
                M2C_FIELD(temp_s0, u16 *, 0x18) = 8U;
            }
            if ((var_s1 == 1) || (var_s1 == 6)) {
                M2C_FIELD(temp_s0, u16 *, 0x18) = (s16) (M2C_FIELD(temp_s0, u16 *, 0x18) - 4);
            }
            if ((var_s1 == 2) || (var_s1 == 5)) {
                M2C_FIELD(temp_s0, u16 *, 0x18) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x18) - 2);
            }
            M2C_FIELD(temp_s0, u16 *, 0x1A) = (u16) M2C_FIELD(arg0_in, u16 *, 0x96);
            M2C_FIELD(temp_s0, s16 *, 0x1C) = var_s1;
            M2C_FIELD(temp_s0, s16 *, 0x1E) = 0;
            M2C_FIELD(temp_s0, s32 *, 0x24) = arg3;
            M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80168C88;
            func_8004491C(temp_v0, &D_80045340);
            temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
            M2C_FIELD(temp_a0, s16 *, 0x10) = 0x20;
            M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x14) | 0x8C);
            temp_a0_2 = M2C_FIELD(temp_v0, void **, 8);
            M2C_FIELD(temp_a0_2, s32 *, 0) = (s32) M2C_FIELD(arg1_reg, s32 *, 0);
            M2C_FIELD(temp_a0_2, s32 *, 4) = (s32) M2C_FIELD(arg1_reg, s32 *, 4);
            M2C_FIELD(temp_a0_2, s32 *, 8) = (s32) (M2C_FIELD(arg1_reg, s32 *, 8) + 0xFFC80000);
            M2C_FIELD(temp_s0, u16 *, 0x8A) = 0U;
            M2C_FIELD(temp_s0, u16 *, 0x84) = 0U;
            M2C_FIELD(temp_s0, u16 *, 0x7E) = 0U;
            M2C_FIELD(temp_s0, u16 *, 0x78) = 0U;
            M2C_FIELD(temp_s0, u16 *, 0x88) = 0U;
            M2C_FIELD(temp_s0, u16 *, 0x82) = 0U;
            M2C_FIELD(temp_s0, u16 *, 0x86) = 0U;
            M2C_FIELD(temp_s0, u16 *, 0x80) = 0U;
            M2C_FIELD(temp_s0, u16 *, 0x74) = (u16) (M2C_FIELD(stack_base, s16 *, (((u16) M2C_FIELD(arg0_work, u16 *, 0x2A) >> 7) & 0x1C)) * 0xF);
            M2C_FIELD(temp_s0, u16 *, 0x7A) = (u16) (M2C_FIELD(stack_base, s16 *, (((u16) M2C_FIELD(arg0_work, u16 *, 0x2A) >> 7) & 0x1C)) * 0xF);
            M2C_FIELD(temp_s0, u16 *, 0x76) = (u16) ((s16) *(volatile u16 *)(((s8 *) stack_base + (((u16) M2C_FIELD(arg0_work, u16 *, 0x2A) >> 7) & 0x1C)) + 2) * 0xF);
            M2C_FIELD(temp_s0, u16 *, 0x7C) = (u16) ((s16) *(volatile u16 *)(((s8 *) stack_base + (((u16) M2C_FIELD(arg0_work, u16 *, 0x2A) >> 7) & 0x1C)) + 2) * 0xF);
            temp_a2 = var_s1 - 1;
            M2C_FIELD(temp_s0, s32 *, 0x5C) = M2C_FIELD(stack_base, s16 *, ((((s32) (M2C_FIELD(arg0_work, u16 *, 0x2A) << 0x10) >> 0x19) + 6) & 7) << 2) * 0x3333;
            coeff_ptr = (u16 *)((s8 *)stack_base + (((((s32) (M2C_FIELD(arg0_work, u16 *, 0x2A) << 0x10) >> 0x19) + 6) & 7) << 2));
            M2C_FIELD(temp_s0, s32 *, 0x60) = (s32) ((s16) coeff_ptr[1] * 0x3333);
            var_a1 = M2C_FIELD(temp_s0, s32 *, 0x5C) * temp_a2;
            if (var_a1 < 0) {
                var_a1 += var_s6;
            }
            var_a0 = M2C_FIELD(temp_s0, volatile s32 *, 0x5C) * temp_a2;
            M2C_FIELD(temp_s0, u16 *, 0x7A) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x7A) + (var_a1 >> 0x10));
            if (var_a0 < 0) {
                var_a0 += var_s6;
            }
            var_a1_2 = M2C_FIELD(temp_s0, s32 *, 0x60) * temp_a2;
            M2C_FIELD(temp_s0, u16 *, 0x86) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x86) + (var_a0 >> 0x10));
            if (var_a1_2 < 0) {
                var_a1_2 += var_s6;
            }
            var_a0_2 = M2C_FIELD(temp_s0, s32 *, 0x60) * temp_a2;
            M2C_FIELD(temp_s0, u16 *, 0x7C) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x7C) + (var_a1_2 >> 0x10));
            if (var_a0_2 < 0) {
                var_a0_2 += var_s6;
            }
            var_a1_3 = M2C_FIELD(temp_s0, s32 *, 0x5C) * var_s1;
            M2C_FIELD(temp_s0, u16 *, 0x88) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x88) + (var_a0_2 >> 0x10));
            if (var_a1_3 < 0) {
                var_a1_3 += var_s6;
            }
            var_a0_3 = M2C_FIELD(temp_s0, s32 *, 0x5C) * var_s1;
            M2C_FIELD(temp_s0, u16 *, 0x74) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x74) + (var_a1_3 >> 0x10));
            if (var_a0_3 < 0) {
                var_a0_3 += var_s6;
            }
            var_a1_4 = M2C_FIELD(temp_s0, s32 *, 0x60) * var_s1;
            M2C_FIELD(temp_s0, u16 *, 0x80) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x80) + (var_a0_3 >> 0x10));
            if (var_a1_4 < 0) {
                var_a1_4 += var_s6;
            }
            var_a0_4 = M2C_FIELD(temp_s0, s32 *, 0x60) * var_s1;
            M2C_FIELD(temp_s0, u16 *, 0x76) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x76) + (var_a1_4 >> 0x10));
            if (var_a0_4 < 0) {
                var_a0_4 += var_s6;
            }
            M2C_FIELD(temp_s0, u16 *, 0x82) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x82) + (var_a0_4 >> 0x10));
            temp_a0_3 = M2C_FIELD(temp_v0, void **, 0xC);
            M2C_FIELD(temp_a0_3, s16 *, 0x1E) = 0x1000;
            M2C_FIELD(temp_a0_3, s16 *, 0x1C) = 0x1000;
            M2C_FIELD(temp_a0_3, u8 *, 0xD) = 0x60U;
            M2C_FIELD(temp_s0, u8 *, 0) = (
                M2C_FIELD(temp_a0_3, u8 *, 0xC) = 0xF0U,
                M2C_FIELD(temp_a0_3, u8 *, 0xE) = 0xFFU,
                M2C_FIELD(temp_a0_3, u8 *, 0xC));
            M2C_FIELD(temp_s0, u8 *, 1) = (u8) M2C_FIELD(temp_a0_3, u8 *, 0xD);
            M2C_FIELD(temp_s0, u8 *, 2) = (u8) M2C_FIELD(temp_a0_3, u8 *, 0xE);
            func_8003DB94(temp_a0_3, &D_800DEAE0, 0);
            M2C_FIELD(((M2C_FIELD(temp_s0, s16 *, 0x1C) * 0x60) + table_base), u16 *, 0) = M2C_FIELD(temp_s0, u16 *, 0x80);
            M2C_FIELD(((M2C_FIELD(temp_s0, s16 *, 0x1C) * 0x60) + table_base), u16 *, 2) = (u16) M2C_FIELD(temp_s0, u16 *, 0x82);
            M2C_FIELD(((M2C_FIELD(temp_s0, s16 *, 0x1C) * 0x60) + table_base), u16 *, 4) = (u16) M2C_FIELD(temp_s0, u16 *, 0x84);
            M2C_FIELD(((M2C_FIELD(temp_s0, s16 *, 0x1C) * 0x60) + table_base), u16 *, 6) = (u16) M2C_FIELD(temp_s0, u16 *, 0x86);
            M2C_FIELD(((M2C_FIELD(temp_s0, s16 *, 0x1C) * 0x60) + table_base), u16 *, 8) = (u16) M2C_FIELD(temp_s0, u16 *, 0x88);
            M2C_FIELD(((M2C_FIELD(temp_s0, s16 *, 0x1C) * 0x60) + table_base), u16 *, 0xA) = (u16) M2C_FIELD(temp_s0, u16 *, 0x8A);
            M2C_FIELD(((M2C_FIELD(temp_s0, s16 *, 0x1C) * 0x60) + table_base), u16 *, 0x54) = (u16) M2C_FIELD(temp_s0, u16 *, 0x74);
            M2C_FIELD(((M2C_FIELD(temp_s0, s16 *, 0x1C) * 0x60) + table_base), u16 *, 0x56) = (u16) M2C_FIELD(temp_s0, u16 *, 0x76);
            M2C_FIELD(((M2C_FIELD(temp_s0, s16 *, 0x1C) * 0x60) + table_base), u16 *, 0x58) = (u16) M2C_FIELD(temp_s0, u16 *, 0x78);
            M2C_FIELD(((M2C_FIELD(temp_s0, s16 *, 0x1C) * 0x60) + table_base), u16 *, 0x5A) = (u16) M2C_FIELD(temp_s0, u16 *, 0x7A);
            M2C_FIELD(((M2C_FIELD(temp_s0, s16 *, 0x1C) * 0x60) + table_base), u16 *, 0x5C) = (u16) M2C_FIELD(temp_s0, u16 *, 0x7C);
            M2C_FIELD(((M2C_FIELD(temp_s0, s16 *, 0x1C) * 0x60) + table_base), u16 *, 0x5E) = (u16) M2C_FIELD(temp_s0, u16 *, 0x7E);
        }
        var_s1 += 1;
    } while (var_s1 < 8);
}
