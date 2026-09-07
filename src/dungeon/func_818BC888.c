#include "common.h"

typedef struct S_818BC888_0_pre {
    u16 unk_00;
} S_818BC888_0_pre;   /* the 0x2 bytes before arg0 in func_818BC888, addressed as arg0[-1] */

typedef struct S_818BC888_0 {
    void * unk_00;
    union { u16 u16; s16 s16; u8 u8; } unk_04;   /* accessed as both */
    u8 pad_06[0x2];
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s8 unk_0E;
} S_818BC888_0;   /* arg0 in func_818BC888 */

typedef struct S_818BC888_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818BC888_1;   /* temp_v1 in func_818BC888 */



extern void func_800240D8() __attribute__((noreturn));
extern void func_8002414C() __attribute__((noreturn));
extern void func_800241C0() __attribute__((noreturn));
extern void func_800241C4() __attribute__((noreturn));
extern s32 D_800814A0[3];

#ifndef NON_MATCHING
register s32 func_818BC888_product_lo ASM_REG("lo");   /* MATCH pin: retail basic-block layout depends on it */
#endif

void func_818BC888(void *arg0) {
    s16 temp_v1_2;
    s32 var_v0_2;
    s32 temp_v1_shifted;
    u16 temp_v0;
    u32 temp_hi;
    u32 temp_lo;
    S_818BC888_1 *temp_v1;

    temp_v1 = ((S_818BC888_0 *)arg0)->unk_00;
    temp_v1->unk_14 = temp_v1->unk_14 + 1;
    temp_v0 = ((S_818BC888_0 *)arg0)->unk_04.u16 + 1;
    ((S_818BC888_0 *)arg0)->unk_04.u16 = temp_v0;
    temp_v1_shifted = ((S_818BC888_0 *)arg0)->unk_0A << 0xB;
    if ((s16)temp_v0 >= 0x20) {
        s32 factor;

        factor = 0x40 - (s16)temp_v0;
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
    ASM_MEM_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    ((S_818BC888_0 *)arg0)->unk_08 = temp_hi;
    temp_v1_2 = ((S_818BC888_0 *)arg0)->unk_04.s16;
    if (temp_v1_2 >= 0x40) {
        ((S_818BC888_0_pre *)arg0)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
        func_800241C4(arg0, (s16)temp_v0, temp_lo);
        return;
    }
    if (temp_v1_2 < 0x10) {
        s32 tail_v0;

        tail_v0 = ((S_818BC888_0 *)arg0)->unk_04.u8 << 3;
        ASM_TAILSLOT_PIN(tail_v0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_8002414C();
        return;
    }
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    if (temp_v1_2 < 0x30) {
        s32 tail_v0;

        tail_v0 = 0x80;
        ASM_TAILSLOT_PIN(tail_v0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_8002414C();
        return;
    }
    ((S_818BC888_0 *)arg0)->unk_0E = -0x80 - ((temp_v1_2 - 0x30) * 8);
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_v1_2 = ((S_818BC888_0 *)arg0)->unk_04.s16 % 4;
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
    if (temp_v1_2 != var_v0_2) {
        var_v0_2 = 0x7E02;
        func_800241C4(arg0, (s16)temp_v0, temp_lo);
        return;
    }
    var_v0_2 = 0x7E02;
    goto store_value;

tail_c0:
    var_v0_2 = 0x7E00;
    ASM_TAILSLOT_PIN(var_v0_2);   /* MATCH pin: retail delay-slot contents depend on it */
    func_800241C0(arg0, (s16)temp_v0, temp_lo);

case_2:
    var_v0_2 = 0x7E01;

store_value:
    ((S_818BC888_0 *)arg0)->unk_0C = var_v0_2;
}
