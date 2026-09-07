#include "common.h"
#include "m2c_compat.h"

extern void *D_80088880[];
extern u16 D_80083168[];

s32 func_8009074C(s16 arg0, u16 *arg1, u16 *arg2) {
    static void *const jt_keep[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12 };
    s32 temp_a0;
    register s16 var_a3 ASM_REG("$7");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 temp_t0;
    register s32 temp_v1_2 ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 var_v0_2;
    s32 var_v0_5;
    register s32 var_v0_6 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    u16 temp_a2;
    u16 temp_v1;
    u16 var_v0;
    u16 normalized;
    u32 global_value;
    u32 temp_v0;

    global_value = D_80083168[0];
    var_a3 = -1;
    temp_t0 = global_value & 0xF000;
    if (global_value & 0x10) {
        goto block_2;
    }
    *arg1 &= 0xFFF;
block_2:
    temp_v0 = global_value >> 0xC;
    if ((u32) (temp_v0 - 1) >= 0xCU) {
        goto block_17;
    }
    (void)jt_keep; goto *D_80088880[(u32)((temp_v0) - 1)];
jt_c2:
    if (*arg1 & temp_t0) {
        goto block_19;
    }
    {
        register s32 tail_v0 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        s32 tail_a3;
        tail_v0 = ((s32) (arg0 << 0x10) >> 7);
        tail_a3 = 0 - tail_v0;
        var_a3 = tail_a3;
        goto block_19;
    }
jt_c6:
    {
        register s32 tail_v1 ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        s32 tail_a3;
        register s32 tail_v0 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        tail_v0 = (s16)arg0;
        tail_v1 = 1 - tail_v0;
        tail_a3 = tail_v1 << 9;
        tail_v0 = (*arg1 & 0xFFF) | temp_t0;
        var_a3 = tail_a3;
        var_v0 = tail_v0;
        goto block_18_c1;
    }
jt_c4:
    if (*arg1 & temp_t0) {
        goto block_19;
    }
    {
        temp_v1_2 = (s16)arg0;
        var_v0_2 = 2;
        goto entry_v0_minus_v1;
    }
jt_c12:
    {
        register s32 tail_v1 ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        s32 tail_a3;
        register s32 tail_v0 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        tail_v0 = (s16)arg0;
        tail_v1 = 3 - tail_v0;
        tail_a3 = tail_v1 << 9;
        tail_v0 = (*arg1 & 0xFFF) | temp_t0;
        var_a3 = tail_a3;
        var_v0 = tail_v0;
        goto block_18_c3;
    }
jt_c8:
    if (*arg1 & temp_t0) {
        goto block_19;
    }
    {
        temp_v1_2 = (s16)arg0;
        var_v0_2 = 4;
        goto entry_v0_minus_v1;
    }
jt_c9:
    {
        register s32 tail_v1 ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        register s32 tail_v0 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        s32 tail_a3;
        tail_v0 = (s16)arg0;
        tail_v1 = 5 - tail_v0;
        tail_a3 = tail_v1 << 9;
        tail_v0 = (*arg1 & 0xFFF) | temp_t0;
        var_a3 = tail_a3;
        var_v0 = tail_v0;
        goto block_18_c5;
    }
jt_c1:
    if (*arg1 & temp_t0) {
        goto block_19;
    }
    temp_v1_2 = (s16)arg0;
    var_v0_2 = 6;
entry_v0_minus_v1:
    var_v0_2 = var_v0_2 - temp_v1_2;
    var_a3 = var_v0_2 << 9;
    goto block_19;
jt_c3:
    {
        register s32 tail_v0 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 tail_v1 ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        s32 tail_a3;
        tail_v0 = (s16)arg0;
        tail_v1 = 7 - tail_v0;
        tail_a3 = tail_v1 << 9;
        tail_v0 = (*arg1 & 0xFFF) | temp_t0;
        var_a3 = tail_a3;
        var_v0 = tail_v0;
        goto block_18_c7;
    }
jt_c5:
jt_c7:
jt_c10:
jt_c11:
block_17:
    var_v0 = *arg1 & 0xFFF;
block_18_c1:
    ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
block_18_c3:
    ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
block_18_c5:
    ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
block_18_c7:
block_18:
    *arg1 = var_v0;
block_19:
    *arg1 &= 0xFBFF;
    if (arg2 == NULL) {
        goto block_34;
    }
    if (var_a3 == -1) {
        goto block_34;
    }
    temp_v1 = *arg2;
    normalized = temp_v1 & 0x800;
    if (!normalized) {
        normalized = temp_v1 & 0x7FF;
    } else {
        normalized = temp_v1 | 0xF800;
    }
block_23:
    *arg2 = normalized;
    normalized = var_a3 & 0x800;
    if (!normalized) {
        normalized = (u16) var_a3 & 0x7FF;
    } else {
        normalized = (u16) var_a3 | 0xF800;
    }
block_25:
    var_a3 = normalized;
    temp_a0 = (s16) *arg2;
    temp_a2 = *arg2;
    var_v0_5 = temp_a0 - var_a3;
    if (var_v0_5 >= 0) {
        goto block_27;
    }
    var_v0_5 = 0 - var_v0_5;
block_27:
    ASM_KEEP(var_a3);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    if (var_v0_5 < 0x801) {
        goto block_28;
    }
    {
        u16 wrap_hi;
        register u16 wrap_lo ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        wrap_hi = temp_a2 & 0xF000;
        ASM_KEEP(wrap_hi);   /* MATCH pin: keeps a statement from moving across a call/branch */
        wrap_lo = var_a3 & 0xFFF;
        ASM_KEEP(wrap_lo);   /* MATCH pin: load-bearing for the whole function shape */
        var_a3 = wrap_hi | wrap_lo;
    }
    var_v0_6 = var_a3 << 0x10;
    goto block_29;
block_28:
    var_v0_6 = var_a3 << 0x10;
block_29:
    temp_v1_2 = var_v0_6 >> 0x10;
    var_v0_2 = temp_a0 < temp_v1_2;
    if (!var_v0_2) {
        goto block_31;
    }
    var_v0 = *arg1;
    var_a3 = temp_a2 + 0x200;
    goto block_33;
block_31:
    var_v0_2 = temp_v1_2 < temp_a0;
    if (!var_v0_2) {
        goto block_34;
    }
    var_v0 = *arg1;
    var_a3 = temp_a2 - 0x200;
block_33:
    var_v0 |= 0x400;
    *arg1 = var_v0;
block_34:
    return var_a3 & 0xFFF;
}
