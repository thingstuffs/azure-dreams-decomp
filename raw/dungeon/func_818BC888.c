#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern void func_800240D8() __attribute__((noreturn));
extern void func_8002414C() __attribute__((noreturn));
extern void func_800241C0() __attribute__((noreturn));
extern void func_800241C4() __attribute__((noreturn));
extern s32 D_800814A0[3];

#ifndef NON_MATCHING
register s32 func_818BC888_product_lo ASM_REG("lo");
#endif

void func_818BC888(void *arg0) {
    s16 temp_v1_2;
    register s32 var_v0_2 ASM_REG("$2");
    s32 temp_v1_shifted;
    u16 temp_v0;
    u32 temp_hi;
    u32 temp_lo;
    void *temp_v1;

    temp_v1 = FIELD(arg0, void *, 0);
    FIELD(temp_v1, u16, 0x14) = FIELD(temp_v1, u16, 0x14) + 1;
    temp_v0 = FIELD(arg0, u16, 4) + 1;
    FIELD(arg0, u16, 4) = temp_v0;
    temp_v1_shifted = FIELD(arg0, s16, 0xA) << 0xB;
    if ((s16)temp_v0 >= 0x20) {
        register s32 factor ASM_REG("$2");

        factor = 0x40 - (s16)temp_v0;
        ASM_KEEP(factor);
#ifndef NON_MATCHING
        func_818BC888_product_lo = factor * temp_v1_shifted;
#endif
        func_800240D8(arg0, (s16)temp_v0);
        return;
    }
#ifndef NON_MATCHING
    func_818BC888_product_lo = (s16)temp_v0 * temp_v1_shifted;
    temp_lo = func_818BC888_product_lo;
#else
    temp_lo = (s16)temp_v0 * temp_v1_shifted;
#endif
    temp_hi = temp_lo >> 0x10;
    ASM_MEM_BARRIER();
    FIELD(arg0, s16, 8) = temp_hi;
    temp_v1_2 = FIELD(arg0, s16, 4);
    if (temp_v1_2 >= 0x40) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        func_800241C4(arg0, (s16)temp_v0, temp_lo);
        return;
    }
    if (temp_v1_2 < 0x10) {
        register s32 tail_v0 ASM_REG("$2");

        tail_v0 = FIELD(arg0, u8, 4) << 3;
        ASM_TAILSLOT_PIN(tail_v0);
        func_8002414C();
        return;
    }
    ASM_SCHED_BARRIER();
    if (temp_v1_2 < 0x30) {
        register s32 tail_v0 ASM_REG("$2");

        tail_v0 = 0x80;
        ASM_TAILSLOT_PIN(tail_v0);
        func_8002414C();
        return;
    }
    FIELD(arg0, s8, 0xE) = -0x80 - ((temp_v1_2 - 0x30) * 8);
    ASM_SCHED_BARRIER();
    temp_v1_2 = FIELD(arg0, s16, 4) % 4;
    if (temp_v1_2 == 1) {
        goto tail_c0;
    }
    if (temp_v1_2 < 2) {
        var_v0_2 = 0x7DCF;
        if (temp_v1_2 != 0) {
            func_800241C4(arg0, (s16)temp_v0, temp_lo);
            return;
        }
        goto store_value;
    }
    if (temp_v1_2 == 2) {
        goto case_2;
    }
    var_v0_2 = 3;
    ASM_KEEP_NV(var_v0_2);
    if (temp_v1_2 != var_v0_2) {
        var_v0_2 = 0x7E02;
        func_800241C4(arg0, (s16)temp_v0, temp_lo);
        return;
    }
    var_v0_2 = 0x7E02;
    goto store_value;

tail_c0:
    var_v0_2 = 0x7E00;
    ASM_TAILSLOT_PIN(var_v0_2);
    func_800241C0(arg0, (s16)temp_v0, temp_lo);

case_2:
    var_v0_2 = 0x7E01;

store_value:
    FIELD(arg0, s16, 0xC) = var_v0_2;
}
