/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80046884();     /* extern */
s32 func_80046C20(); /* extern */
M2C_UNK func_80064624();                    /* extern */
M2C_UNK func_80064D20();                      /* extern */
M2C_UNK func_80064D50();                      /* extern */
void func_800AC550(void) __attribute__((noreturn)); /* extern */
void func_800AC7F4(void) __attribute__((noreturn)); /* extern */
void func_800AC7F8(void) __attribute__((noreturn)); /* extern */
void func_800AC860(void) __attribute__((noreturn)); /* extern */
void func_800AC868(void) __attribute__((noreturn)); /* extern */
void func_800ACA88(void) __attribute__((noreturn)); /* extern */
void func_800ACED4(void) __attribute__((noreturn)); /* extern */
void func_800ACFF8(void) __attribute__((noreturn)); /* extern */
M2C_UNK func_800AD138();                         /* extern */
extern u8 D_8006ADBC[];
extern u8 D_80083160[];
extern s32 D_800D1548[3];
extern u8 D_800D1554[9];

void func_800AC4C4(void) {
    s32 temp_a3;
    s32 c0idx;
    s32 temp_t0;
    s32 init_t1;
    s32 init_t2;
    s32 init_t3;
    s32 init_v0;
    void *init_v1;
    u8 init_t4;
    u32 init_byte;
    s32 *temp_a0;
    s32 *temp_v1_9;
    s8 *temp_s2;
    s8 *temp_s3;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 temp_v1_7;
    register s32 temp_v1_8 ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */
    register s32 tail_v0 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 var_a0_2;
    M2C_UNK * var_a0_3;
    register s32 var_a2 ASM_REG("$6");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 var_a2_2;
    s8 *var_s6;
    s32 var_v1;
    u16 temp_v1_10;
    u32 temp_v0_5;
    M2C_UNK * var_s0;
    void *temp_s0;
    register void *temp_s5 ASM_REG("$21");   /* MATCH pin: load-bearing for the whole function shape */
    void *temp_t6;
    void *var_a0;
    void *var_a1;
    void *var_a2_3;
    void *var_a3;
    void *var_t0;
    void *var_v1_2;
    void *inner_p;
    register s32 inner_add ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
    register s32 inner_sub ASM_REG("$7");   /* MATCH pin: retail register colouring depends on it */
    s32 row_limit;
    register void *call_a0 ASM_REG("$4");   /* MATCH pin: retail keeps a computation the compiler would drop */
    register void *call_a1 ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register void *call_a2 ASM_REG("$6");   /* MATCH pin: keeps a constant in a register as retail does */
    void *call_a3;
    u32 tag_low_mask;
    u32 tag_high_mask;
    s32 one;
    s8 *gte;
    register void *gte_input ASM_REG("$13");   /* MATCH pin: retail register colouring depends on it */
    register u8 *d_80083160 ASM_REG("$20");   /* MATCH pin: load-bearing for the whole function shape */

    {
        register u8 *page8008 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        page8008 = (u8 *)0x80080000;
        ASM_KEEP_NV(page8008);   /* MATCH pin: retail immediate-load split depends on it */
        d_80083160 = page8008 + 0x3160;
    }
    ASM_KEEP_NV(d_80083160);   /* MATCH pin: load-bearing for the whole function shape */
    temp_s5 = d_80083160 + 0x1DC;
    var_s6 = M2C_FIELD(d_80083160, s8 **, 0x1DC);
    temp_s2 = M2C_FIELD(temp_s5, s8 **, 8);
    temp_s3 = M2C_FIELD(temp_s5, s8 **, 0xC);
    func_80064D50(d_80083160 + 0x70);
    {
        u8 *base18;
        base18 = d_80083160 + 0x18;
        func_80064624(M2C_FIELD(base18, s32 *, 0x84), M2C_FIELD(base18, s32 *, 0x88));
    }
    gte = (s8 *)0x1F800000;
    ASM_KEEP_NV(gte);   /* MATCH pin: retail immediate-load split depends on it */
    func_80064D20(d_80083160 + 0x50);
    if (D_800D1554[0] != 0) {
        M2C_FIELD(d_80083160, s16 *, 0x1A) = -0xB8;
        tail_v0 = 0x1DA;
        ASM_TAILSLOT_PIN_TIED(tail_v0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_800AC550();
        return;
    }
    ASM_KEEP(d_80083160);   /* MATCH pin: load-bearing for the whole function shape */
    M2C_FIELD(d_80083160, s16 *, 0x1A) = -0x88;
    M2C_FIELD(d_80083160, s16 *, 0x1E) = 0x1AA;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_s0 = d_80083160 + 0x20;
    func_80046884(d_80083160 + 0x18, temp_s0, 0);
    call_a0 = temp_s0;
    call_a1 = (void *) ((u32) gte | 0x1C);
    init_v0 = M2C_FIELD(d_80083160, s32 *, 0xA8);
    call_a2 = (void *) ((u32) gte | 0x174);
    M2C_FIELD(gte, s32 *, 0) = init_v0;
    init_v1 = M2C_FIELD(d_80083160, void **, 0);
    temp_a3 = M2C_FIELD(temp_s5, s16 *, 0x14);
    temp_t0 = M2C_FIELD(temp_s5, s16 *, 0x16);
    init_t1 = M2C_FIELD(temp_s5, s16 *, 0x18);
    init_t2 = M2C_FIELD(temp_s5, s16 *, 0x1A);
    {
        u8 *page;
        page = (u8 *)0x80010000;
        init_t3 = M2C_FIELD(page, s32 *, 0x3180);
        init_t4 = M2C_FIELD(page, u8 *, 0x3184);
        init_byte = M2C_FIELD(page, u8 *, 0x3185);
    }
    init_v1 += 0xB0;
    M2C_FIELD(gte, s32 *, 0x124) = (s32) temp_a3;
    M2C_FIELD(gte, volatile u16 *, 0x178) = init_byte;
    M2C_FIELD(gte, s32 *, 0x0BC) = init_v1;
    M2C_FIELD(gte, s32 *, 0x128) = (s32) temp_t0;
    M2C_FIELD(gte, s32 *, 0x114) = 0x40 << M2C_FIELD(gte, s32 *, 0x124);
    M2C_FIELD(gte, s32 *, 0x11C) = (s32) init_t1;
    M2C_FIELD(gte, s32 *, 0x120) = (s32) init_t2;
    M2C_FIELD(gte, s32 *, 0x110) = init_t3;
    M2C_FIELD(gte, u16 *, 0x176) = init_t4;
    call_a3 = M2C_FIELD(d_80083160, void **, 0);
    M2C_FIELD(gte, s32 *, 0x118) = 0x40 << M2C_FIELD(gte, s32 *, 0x128);
    var_s0 = M2C_FIELD(call_a3, u32 *, 0x8D0);
    M2C_FIELD(gte, s32 *, 0x14C) = 0xFFFF;
    M2C_FIELD(gte, u16 *, 0x174) = 4;
    M2C_FIELD(gte, s32 *, 0x164) = (u8 *) var_s0 + 0xCCCC;
    M2C_FIELD(gte, s32 *, 0x00C) = (s16) func_80046C20(call_a0, call_a1, call_a2, call_a3);
    if (M2C_FIELD(gte, u16 *, 0x174) != 0) {
        one = 1;
        gte_input = gte + 0xE0;
        temp_t6 = D_800D1548;
        tag_low_mask = 0xFFFFFF;
        tag_high_mask = 0xFF000000;
loop_5:
        var_a2 = 3;
        var_a0 = (s32 *)(gte + 0x78);
        do {
            if (M2C_FIELD(var_a0, s32 *, 0x38) == 0) {
                temp_v1_8 = M2C_FIELD(var_a0, s32 *, 0x34);
                tail_v0 = M2C_FIELD(gte, s32 *, 0x00C);
                if (tail_v0 >= temp_v1_8) {
                    M2C_FIELD(var_a0, s32 *, 0x38) = one;
                }
            }
            var_a2 -= 1;
            var_a0 -= 0x28;
        } while (var_a2 >= 0);
        var_a2_2 = 3;
        var_a1 = (s32 *)(gte + 0x78);
        M2C_FIELD(gte, s32 *, 0x014) = 0x7FFF;
        M2C_FIELD(gte, s32 *, 0x018) = -0x7FFF;
        do {
            if (M2C_FIELD(var_a1, s32 *, 0x38) > 0) {
                temp_v1 = M2C_FIELD(var_a1, s32 *, 0x1C);
                M2C_FIELD(gte, s32 *, 0x008) = temp_v1;
                if (temp_v1 < M2C_FIELD(gte, s32 *, 0x014)) {
                    M2C_FIELD(gte, s32 *, 0x014) = temp_v1;
                }
                temp_v1_2 = M2C_FIELD(gte, s32 *, 0x008);
                if (M2C_FIELD(gte, s32 *, 0x018) < temp_v1_2) {
                    M2C_FIELD(gte, s32 *, 0x018) = temp_v1_2;
                }
                temp_v1_3 = M2C_FIELD(var_a1, s32 *, 0x2C) + M2C_FIELD(var_a1, s32 *, 0x24);
                M2C_FIELD(var_a1, s32 *, 0x2C) = temp_v1_3;
                if (temp_v1_3 >= 0) {
                    inner_p = var_a1;
                    inner_add = M2C_FIELD(var_a1, s32 *, 0x30);
                    inner_sub = M2C_FIELD(var_a1, s32 *, 0x20);
loop_18:
                    tail_v0 = M2C_FIELD(inner_p, s32 *, 0x1C);
                    temp_v1_8 = M2C_FIELD(inner_p, s32 *, 0x3C);
                    tail_v0 += inner_add;
                    M2C_FIELD(inner_p, s32 *, 0x1C) = tail_v0;
                    tail_v0 = M2C_FIELD(inner_p, s32 *, 0x2C);
                    temp_v1_8 -= 0x40;
                    M2C_FIELD(inner_p, s32 *, 0x3C) = temp_v1_8;
                    tail_v0 -= inner_sub;
                    M2C_FIELD(inner_p, s32 *, 0x2C) = tail_v0;
                    if (temp_v1_8 > 0) {
                        if (tail_v0 >= 0) {
                            goto loop_18;
                        }
                    }
                }
                temp_v1_5 = M2C_FIELD(var_a1, s32 *, 0x1C);
                M2C_FIELD(gte, s32 *, 0x008) = temp_v1_5;
                if (temp_v1_5 < M2C_FIELD(gte, s32 *, 0x014)) {
                    M2C_FIELD(gte, s32 *, 0x014) = temp_v1_5;
                }
                temp_v1_6 = M2C_FIELD(gte, s32 *, 0x008);
                if (M2C_FIELD(gte, s32 *, 0x018) < temp_v1_6) {
                    M2C_FIELD(gte, s32 *, 0x018) = temp_v1_6;
                }
            }
            var_a2_2 -= 1;
            var_a1 -= 0x28;
        } while (var_a2_2 >= 0);
        M2C_FIELD(gte, s32 *, 0x014) = (M2C_FIELD(gte, s32 *, 0x014) - 0x20) & ~0x3F;
        var_a0_2 = *(volatile s32 *)(gte + 0x014);
        M2C_FIELD(gte, s32 *, 0x018) = (M2C_FIELD(gte, s32 *, 0x018) + 0x20) & ~0x3F;
        if (var_a0_2 < 0) {
            var_a0_2 += 0x3F;
        }
        var_v1 = M2C_FIELD(gte, s32 *, 0x00C);
        M2C_FIELD(gte, s32 *, 0x134) = var_a0_2 >> 6;
        if (var_v1 < 0) {
            var_v1 += 0x3F;
        }
        temp_v1_7 = var_v1 >> 6;
        M2C_FIELD(gte, s32 *, 0x138) = temp_v1_7;
        if (temp_v1_7 < 0) {
            M2C_FIELD(gte, s32 *, 0x138) = 0;
            func_800AC7F8();
            return;
        }
        row_limit = M2C_FIELD(gte, s32 *, 0x120);
        if (temp_v1_7 >= row_limit) {
            tail_v0 = row_limit << M2C_FIELD(gte, s32 *, 0x124);
            ASM_TAILSLOT_PIN_TIED(tail_v0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            func_800AC7F4();
            return;
        }
        M2C_FIELD(gte, s32 *, 0x138) = temp_v1_7 << M2C_FIELD(gte, s32 *, 0x124);
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        temp_v1_8 = M2C_FIELD(gte, s32 *, 0x014);
        tail_v0 = M2C_FIELD(gte, s32 *, 0x018);
        var_a2_3 = (void *)3;
        if (tail_v0 >= temp_v1_8) {
            var_t0 = (s8 *) var_s0 + 0x20;
loop_37:
            temp_v1_8 = M2C_FIELD(gte, s32 *, 0x134);
            if (temp_v1_8 < 0) {
                tail_v0 = M2C_FIELD(gte, s32 *, 0x138);
                temp_v1_8 &= 3;
                ASM_KEEP(tail_v0);   /* MATCH pin: retail delay-slot fill depends on it */
                ASM_TAILSLOT_PIN_TIED(temp_v1_8);   /* MATCH pin: retail delay-slot contents depend on it */
                func_800AC860();
                return;
            }
            var_a0_3 = M2C_FIELD(gte, s32 *, 0x11C);
            if (temp_v1_8 >= (s32) var_a0_3) {
                tail_v0 = M2C_FIELD(gte, s32 *, 0x138);
                temp_v1_8 &= 3;
                tail_v0 += (s32) var_a0_3;
                tail_v0 += temp_v1_8;
                tail_v0 -= 3;
                ASM_TAILSLOT_PIN_TIED(tail_v0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                func_800AC868();
                return;
            }
            M2C_FIELD(gte, s32 *, 0x144) = M2C_FIELD(gte, s32 *, 0x138) + temp_v1_8;
            temp_v0_3 = M2C_FIELD(var_s6 + (M2C_FIELD(gte, volatile s32 *, 0x144) * 2), u16 *, 0) & 0x3FFF;
            M2C_FIELD(gte, s32 *, 0x0C0) = temp_v0_3;
            if (temp_v0_3 != 0) {
                temp_v0_4 = M2C_FIELD(var_s6 + (M2C_FIELD(gte, s32 *, 0x144) * 2), u16 *, 0) & 0xC000;
                M2C_FIELD(gte, s32 *, 0x17C) = temp_v0_4;
                if (temp_v0_4 != 0) {
                    M2C_FIELD(gte, s16 *, 0x0FC) = 0;
                    M2C_FIELD(gte, s16 *, 0x0F4) = 0;
                    M2C_FIELD(gte, s16 *, 0x0EC) = 0;
                    M2C_FIELD(gte, s16 *, 0x0E4) = 0;
                    M2C_FIELD(gte, s32 *, 0x0E0) = (u16) M2C_FIELD(gte, s32 *, 0x014) | (M2C_FIELD(gte, s32 *, 0x00C) << 0x10);
                    M2C_FIELD(gte, s32 *, 0x0E8) = ((M2C_FIELD(gte, volatile u16 *, 0x014) + 0x40) & 0xFFFF) | (M2C_FIELD(gte, s32 *, 0x00C) << 0x10);
                    M2C_FIELD(gte, s32 *, 0x0F0) = (u16) M2C_FIELD(gte, s32 *, 0x014) | ((M2C_FIELD(gte, s32 *, 0x00C) + 0x40) << 0x10);
                    M2C_FIELD(gte, s32 *, 0x0F8) = ((M2C_FIELD(gte, volatile u16 *, 0x014) + 0x40) & 0xFFFF) | ((M2C_FIELD(gte, s32 *, 0x00C) + 0x40) << 0x10);
                    gte_ldv3(gte_input, gte + 0xE8, gte + 0xF0);
                    M2C_FIELD(var_t0, s32 *, -0x1C) = 0x2C404040;
                    gte_rtpt_nn();
                    gte_avsz3();
                    gte_stotz(gte + 0xC8);
                    gte_stsxy3_g3(var_s0);
                    gte_ldv0(gte + 0xF8);
                    M2C_FIELD(var_t0, s32 *, -0x14) = (s32) D_800D1548[0];
                    gte_rtps_nn();
                    gte_stsxy(var_t0);
                    M2C_FIELD(var_t0, s32 *, -0xC) = (s32) M2C_FIELD(temp_t6, s32 *, 4);
                    M2C_FIELD(var_t0, u16 *, -4) = (u16) M2C_FIELD(temp_t6, u16 *, 8);
                    M2C_FIELD(var_t0, u16 *, 4) = (u16) M2C_FIELD(temp_t6, u16 *, 0xA);
                    gte_stszotz(gte + 0xD4);
                    call_a0 = (void *)M2C_FIELD(gte, s32 *, 0x0D4);
                    tail_v0 = M2C_FIELD(gte, s32 *, 0x0C8);
                    temp_v1_8 = tail_v0 << 1;
                    tail_v0 += temp_v1_8;
                    tail_v0 += (s32)call_a0;
                    tail_v0 += 3;
                    tail_v0 >>= 2;
                    tail_v0 += 4;
                    M2C_FIELD(gte, s32 *, 0x0C8) = tail_v0;
                    if ((u32)tail_v0 >= 0x200U) {
                        M2C_FIELD(gte, s32 *, 0x0C8) = 0x1FF;
                    }
                    M2C_FIELD(var_t0, s8 *, -0x1D) = 9;
                    var_t0 += 0x28;
                    var_a0_3 = (s32) var_s0 & tag_low_mask;
                    *var_s0 = (s32) ((*var_s0 & tag_high_mask) | (M2C_FIELD((s8 *)M2C_FIELD(gte, s32 *, 0x0BC) + (M2C_FIELD(gte, s32 *, 0x0C8) * 4), s32 *, 0) & tag_low_mask));
                    temp_v1_9 = (M2C_FIELD(gte, s32 *, 0x0C8) * 4) + M2C_FIELD(gte, s32 *, 0x0BC);
                    var_s0 = (s32 *)((s8 *)var_s0 + 0x28);
                    *temp_v1_9 = (*temp_v1_9 & tag_high_mask) | (s32) var_a0_3;
                }
                c0idx = M2C_FIELD(gte, s32 *, 0x0C0);
                ASM_USE_NV(c0idx);   /* MATCH pin: retail schedule: same instructions, different order without it */
                var_a3 = (s8 *)var_s0 + 4;
                ASM_KEEP(var_a3);   /* MATCH pin: retail delay-slot fill depends on it */
                M2C_FIELD(gte, s32 *, 0x12C) = 0;
                    var_a2_3 = M2C_FIELD((s8 *)M2C_FIELD(temp_s5, s32 *, 4) + (c0idx * 4), u8 **, 0);
                if (M2C_FIELD(var_a2_3, s32 *, 0xC) != 0) {
                    tail_v0 = M2C_FIELD(var_a2_3, s32 *, 0x10);
                    call_a0 = (void *) (u32) M2C_FIELD(gte, u16 *, 0x014);
                    M2C_FIELD(gte, s32 *, 0x170) = tail_v0;
                    tail_v0 = M2C_FIELD(var_a2_3, u16 *, 0);
                    temp_v1_8 = M2C_FIELD(var_a2_3, s32 *, 0x14);
                    tail_v0 <<= 3;
                    tail_v0 += (s32) temp_s2;
                    M2C_FIELD(gte, s32 *, 0x16C) = temp_v1_8;
                    tail_v0 = M2C_FIELD((void *) tail_v0, s32 *, 0);
                    temp_v1_8 = M2C_FIELD(gte, u16 *, 0x12C);
                    M2C_FIELD(gte, s32 *, 0x168) = tail_v0;
                    tail_v0 = M2C_FIELD(var_a2_3, u16 *, 0);
                    call_a1 = (void *) (u32) M2C_FIELD(gte, u16 *, 0x168);
                    tail_v0 <<= 3;
                    tail_v0 += (s32) temp_s2;
                    call_a0 = (void *) ((u32) call_a0 + (u32) call_a1);
                    tail_v0 = M2C_FIELD((void *) tail_v0, u16 *, 4);
                    call_a0 = (void *) ((u32) call_a0 & 0xFFFF);
                    tail_v0 -= temp_v1_8;
                    M2C_FIELD(gte, s16 *, 0x0E4) = tail_v0;
                    tail_v0 = M2C_FIELD(gte, u16 *, 0x16A);
                    temp_v1_8 = M2C_FIELD(gte, s32 *, 0x00C);
                    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
                    ASM_KEEP_NV(tail_v0);   /* MATCH pin: retail delay-slot fill depends on it */
                    tail_v0 = (s32) (tail_v0 << 0x10) >> 0x10;
                    temp_v1_8 += tail_v0;
                    temp_v1_8 <<= 0x10;
                    tail_v0 = M2C_FIELD(var_a2_3, u16 *, 2);
                    call_a0 = (void *) ((u32) call_a0 | (u32) temp_v1_8);
                    M2C_FIELD(gte, s32 *, 0x0E0) = (s32) call_a0;
                    call_a0 = (void *) (u32) M2C_FIELD(gte, u16 *, 0x014);
                    temp_v1_8 = M2C_FIELD(gte, u16 *, 0x12C);
                    tail_v0 <<= 3;
                    tail_v0 += (s32) temp_s2;
                    tail_v0 = M2C_FIELD((void *) tail_v0, s32 *, 0);
                    M2C_FIELD(gte, s32 *, 0x168) = tail_v0;
                    tail_v0 = M2C_FIELD(var_a2_3, u16 *, 2);
                    call_a1 = (void *) (u32) M2C_FIELD(gte, u16 *, 0x168);
                    tail_v0 <<= 3;
                    tail_v0 += (s32) temp_s2;
                    call_a0 = (void *) ((u32) call_a0 + (u32) call_a1);
                    tail_v0 = M2C_FIELD((void *) tail_v0, u16 *, 4);
                    call_a0 = (void *) ((u32) call_a0 & 0xFFFF);
                    tail_v0 -= temp_v1_8;
                    M2C_FIELD(gte, s16 *, 0x0EC) = tail_v0;
                    tail_v0 = M2C_FIELD(gte, u16 *, 0x16A);
                    temp_v1_8 = M2C_FIELD(gte, s32 *, 0x00C);
                    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
                    ASM_KEEP_NV(tail_v0);   /* MATCH pin: retail delay-slot fill depends on it */
                    tail_v0 = (s32) (tail_v0 << 0x10) >> 0x10;
                    temp_v1_8 += tail_v0;
                    temp_v1_8 <<= 0x10;
                    tail_v0 = M2C_FIELD(var_a2_3, u16 *, 4);
                    call_a0 = (void *) ((u32) call_a0 | (u32) temp_v1_8);
                    M2C_FIELD(gte, s32 *, 0x0E8) = (s32) call_a0;
                    call_a0 = (void *) (u32) M2C_FIELD(gte, u16 *, 0x014);
                    tail_v0 <<= 3;
                    tail_v0 += (s32) temp_s2;
                    tail_v0 = M2C_FIELD((void *) tail_v0, s32 *, 0);
                    M2C_FIELD(gte, s32 *, 0x168) = tail_v0;
                    tail_v0 = M2C_FIELD(gte, u16 *, 0x168);
                    temp_v1_8 = M2C_FIELD(gte, volatile u16 *, 0x16A);
                    call_a0 = (void *) ((u32) call_a0 + (u32) tail_v0);
                    call_a0 = (void *) ((u32) call_a0 & 0xFFFF);
                    temp_v1_8 <<= 0x10;
                    tail_v0 = M2C_FIELD(gte, s32 *, 0x00C);
                    temp_v1_8 >>= 0x10;
                    tail_v0 += temp_v1_8;
                    tail_v0 <<= 0x10;
                    call_a0 = (void *) ((u32) call_a0 | (u32) tail_v0);
                    M2C_FIELD(gte, s32 *, 0x0F0) = (s32) call_a0;
                    tail_v0 = M2C_FIELD(var_a2_3, u16 *, 4);
                    tail_v0 <<= 3;
                    tail_v0 += (s32) temp_s2;
                    temp_v1_8 = M2C_FIELD((void *) tail_v0, u16 *, 4);
                    tail_v0 = M2C_FIELD(gte, u16 *, 0x12C);
                    temp_v1_8 -= tail_v0;
                    M2C_FIELD(gte, s16 *, 0x0F4) = temp_v1_8;
                    gte_ldv3(gte_input, gte + 0xE8, gte + 0xF0);
                    gte_rtpt();
                    gte_nclip();
                    gte_stopz(gte + 0xDC);
                    if (M2C_FIELD(gte, s32 *, 0x0DC) >= 0) {
                        tail_v0 = M2C_FIELD(var_a2_3, u16 *, 6);
                        tail_v0 <<= 3;
                        tail_v0 += (s32) temp_s2;
                        temp_v1_8 = M2C_FIELD((void *) tail_v0, u16 *, 4);
                        tail_v0 = M2C_FIELD(gte, u16 *, 0x12C);
                        temp_v1_8 -= tail_v0;
                        M2C_FIELD(gte, s16 *, 0x0FC) = temp_v1_8;
                        gte_stsxy3_g3(var_s0);
                        gte_avsz3();
                        gte_stotz(gte + 0xC8);
                        temp_v1_10 = (u16) M2C_FIELD(gte, s32 *, 0x170);
                        if (M2C_FIELD(gte, s32 *, 0x14C) != temp_v1_10) {
                            M2C_FIELD(gte, s32 *, 0x14C) = (s32) temp_v1_10;
                            gte_ldrgb(gte);
                            gte_ldv0(temp_s3 + (temp_v1_10 * 8));
                            gte_nccs();
                            gte_strgb(gte + 4);
                        }
                        tail_v0 = M2C_FIELD(var_a2_3, u16 *, 6);
                        call_a0 = (void *) (u32) M2C_FIELD(gte, u16 *, 0x014);
                        tail_v0 <<= 3;
                        tail_v0 += (s32) temp_s2;
                        tail_v0 = M2C_FIELD((void *) tail_v0, s32 *, 0);
                        M2C_FIELD(gte, s32 *, 0x168) = tail_v0;
                        tail_v0 = M2C_FIELD(gte, u16 *, 0x168);
                        temp_v1_8 = M2C_FIELD(gte, volatile u16 *, 0x16A);
                        call_a0 = (void *) ((u32) call_a0 + (u32) tail_v0);
                        call_a0 = (void *) ((u32) call_a0 & 0xFFFF);
                        temp_v1_8 <<= 0x10;
                        tail_v0 = M2C_FIELD(gte, s32 *, 0x00C);
                        temp_v1_8 >>= 0x10;
                        tail_v0 += temp_v1_8;
                        tail_v0 <<= 0x10;
                        call_a0 = (void *) ((u32) call_a0 | (u32) tail_v0);
                        M2C_FIELD(gte, s32 *, 0x0F8) = (s32) call_a0;
                        gte_ldv0(gte + 0xF8);
                        M2C_FIELD(var_a3, s32 *, 8) = (s32) M2C_FIELD(var_a2_3, s32 *, 8);
                        gte_rtps_nn();
                        M2C_FIELD(var_a3, s32 *, 0x10) = (s32) M2C_FIELD(var_a2_3, s32 *, 0xC);
                        M2C_FIELD(var_a3, u16 *, 0x18) = (u16) M2C_FIELD(gte, s32 *, 0x172);
                        M2C_FIELD(var_a3, u16 *, 0x20) = (u16) M2C_FIELD(gte, s32 *, 0x16C);
                        gte_stsxy(var_t0);
                        gte_stszotz(gte + 0xD4);
                        call_a0 = (void *)M2C_FIELD(gte, s32 *, 0x0D4);
                        tail_v0 = M2C_FIELD(gte, s32 *, 0x0C8);
                        temp_v1_8 = tail_v0 << 1;
                        tail_v0 += temp_v1_8;
                        tail_v0 += (s32)call_a0;
                        tail_v0 += 3;
                        tail_v0 >>= 2;
                        M2C_FIELD(gte, s32 *, 0x0C8) = tail_v0;
                        if ((u32) tail_v0 >= 0x200U) {
                            M2C_FIELD(gte, s32 *, 0x0C8) = 0x1FF;
                        }
                        if ((((s32) M2C_FIELD(gte, s32 *, 0x0C8) < 0x1C1) || ((s32) (M2C_FIELD(gte, u16 *, 0x0E4) << 0x10) >= 0) || ((tail_v0 = M2C_FIELD(gte, s32 *, 0x14C), tail_v0 <<= 3, call_a0 = (void *)(tail_v0 + (s32)temp_s3), var_a0_3 = call_a0, (M2C_FIELD(var_a0_3, s16 *, 4) < 0)) && !(M2C_FIELD(var_a0_3, s32 *, 0) & 0x0FFF0FFF))) && ((u32) M2C_FIELD(gte, s32 *, 0x0C8) < 0x200U)) {
                            M2C_FIELD(var_a3, s8 *, -1) = 9;
                            M2C_FIELD(var_a3, s32 *, 0) = (s32) M2C_FIELD(gte, s32 *, 0x004);
                            if (M2C_FIELD(gte, u8 *, 0x16F) & 1) {
                                M2C_FIELD(var_a3, u8 *, 3) |= 2;
                                func_800ACED4();
                                return;
                            }
                            tail_v0 = 0xC000;
                            temp_v1_8 = M2C_FIELD(gte, s32 *, 0x17C) & 0xC000;
                            if (temp_v1_8 == tail_v0) {
                                tail_v0 = M2C_FIELD(var_a3, s32 *, 0xC);
                                temp_v1_8 = M2C_FIELD(var_a3, s32 *, 0x14);
                                call_a0 = M2C_FIELD(var_a3, void **, 0x1C);
                                var_t0 += 0x28;
                                M2C_FIELD(var_a3, s32 *, 8) = tail_v0;
                                M2C_FIELD(var_a3, s32 *, 0xC) = temp_v1_8;
                                M2C_FIELD(var_a3, s32 *, 0x10) = (s32) call_a0;
                                temp_v1_8 = M2C_FIELD(gte, s32 *, 0x110);
                                tail_v0 = 5;
                                M2C_FIELD(var_a3, s8 *, -1) = tail_v0;
                                M2C_FIELD(var_a3, s32 *, 0) = temp_v1_8;
                                var_a3 += 0x28;
                                tail_v0 = M2C_FIELD(gte, s32 *, 0x0C8);
                                temp_v1_8 = M2C_FIELD(gte, s32 *, 0x0BC);
                                tail_v0 <<= 2;
                                tail_v0 += temp_v1_8;
                                temp_v1_8 = *var_s0;
                                tail_v0 = M2C_FIELD((void *)tail_v0, s32 *, 0);
                                temp_v1_8 &= tag_high_mask;
                                tail_v0 &= tag_low_mask;
                                temp_v1_8 |= tail_v0;
                                *var_s0 = temp_v1_8;
                                call_a0 = (void *)(M2C_FIELD(gte, s32 *, 0x0C8) * 4);
                                tail_v0 = M2C_FIELD(gte, s32 *, 0x0BC);
                                call_a0 = (void *)((s32)call_a0 + tail_v0);
                                tail_v0 = (s32) var_s0 & tag_low_mask;
                                temp_v1_8 = M2C_FIELD(call_a0, s32 *, 0);
                                var_s0 = (s32 *)((s8 *)var_s0 + 0x28);
                                temp_v1_8 &= tag_high_mask;
                                temp_v1_8 |= tail_v0;
                                M2C_FIELD(call_a0, s32 *, 0) = temp_v1_8;
                                M2C_FIELD(var_a3, s8 *, -1) = one;
                                temp_v1_8 = M2C_FIELD(gte, u16 *, 0x176);
                                tail_v0 = 0xE1000000;
                                temp_v1_8 &= 0x9FF;
                                temp_v1_8 |= tail_v0;
                                M2C_FIELD(var_a3, s32 *, 0) = temp_v1_8;
                            }
                            var_a3 += 0x28;
                            ASM_KEEP(var_a3);   /* MATCH pin: retail delay-slot fill depends on it */
                            var_t0 += 0x28;
                            tail_v0 = M2C_FIELD(gte, s32 *, 0x0C8);
                            temp_v1_8 = M2C_FIELD(gte, s32 *, 0x0BC);
                            tail_v0 <<= 2;
                            tail_v0 += temp_v1_8;
                            temp_v1_8 = *var_s0;
                            tail_v0 = M2C_FIELD((void *)tail_v0, s32 *, 0);
                            temp_v1_8 &= tag_high_mask;
                            tail_v0 &= tag_low_mask;
                            temp_v1_8 |= tail_v0;
                            *var_s0 = temp_v1_8;
                            call_a0 = (void *)(M2C_FIELD(gte, s32 *, 0x0C8) * 4);
                            tail_v0 = M2C_FIELD(gte, s32 *, 0x0BC);
                            call_a0 = (void *)((s32)call_a0 + tail_v0);
                            temp_v1_8 = M2C_FIELD(call_a0, s32 *, 0);
                            tail_v0 = (s32) var_s0 & tag_low_mask;
                            var_s0 = (s32 *)((s8 *)var_s0 + 0x28);
                            temp_v1_8 &= tag_high_mask;
                            temp_v1_8 |= tail_v0;
                            M2C_FIELD(call_a0, s32 *, 0) = temp_v1_8;
                            temp_v1_8 = M2C_FIELD(gte, u8 *, 0x16E);
                            if ((temp_v1_8 & 0xF) == one) {
                                tail_v0 = M2C_FIELD(gte, u8 *, 0x16F);
                                tail_v0 <<= 0x18;
                                if (tail_v0 >= 0) {
                                    temp_v1_8 = (u32) temp_v1_8 >> 4;
                                    tail_v0 = temp_v1_8 * 3;
                                    tail_v0 *= 8;
                                    tail_v0 += 0x18;
                                    var_a2_3 = (s8 *) var_a2_3 + tail_v0;
                                    ASM_TAILSLOT_PIN_TIED(var_a2_3);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                                    func_800ACA88();
                                    return;
                                }
                                goto block_80;
                            }
                            goto tail_aca88_18;
                        }
                        goto block_80;
                    }
                    if (M2C_FIELD((((u16) M2C_FIELD(gte, s32 *, 0x170) * 8) + temp_s3), s16 *, 4) < 0) {
                        if (M2C_FIELD(gte, u8 *, 0x16E) == one) {
                            tail_v0 = (s32) M2C_FIELD(gte, u8 *, 0x16F) << 0x18;
                            ASM_TAILSLOT_PIN_TIED(tail_v0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                            func_800ACFF8();
                            return;
                        }
                        goto tail_aca88_18;
                    }
                    temp_v1_8 = M2C_FIELD(gte, u8 *, 0x16E);
                    if (temp_v1_8 & 0xF0) {
                        goto tail_aca88_scaled;
                    }
                    tail_v0 = M2C_FIELD(gte, u8 *, 0x16F);
                    tail_v0 <<= 0x18;
                    if (tail_v0 >= 0) {
tail_aca88_scaled:
                        temp_v1_8 &= 0xF;
                        tail_v0 = temp_v1_8 * 3;
                        tail_v0 *= 8;
                        var_a2_3 = (s8 *) var_a2_3 + tail_v0;
                        ASM_TAILSLOT_PIN_TIED(var_a2_3);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                        func_800ACA88();
                        return;
                    }
                    goto block_80;
                }
                if ((M2C_FIELD(var_a2_3, u8 *, 0x16) != one) || (M2C_FIELD(var_a2_3, s8 *, 0x17) >= 0)) {
tail_aca88_18:
                    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
                    var_a2_3 = (s8 *) var_a2_3 + 0x18;
                    ASM_TAILSLOT_PIN_TIED(var_a2_3);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                    func_800ACA88();
                    return;
                }
block_80:
                if ((u32) M2C_FIELD(gte, s32 *, 0x164) >= var_s0) {
                    goto block_81;
                }
                goto block_89;
            }
block_81:
            M2C_FIELD(gte, s32 *, 0x134) += 1;
            temp_v0_8 = M2C_FIELD(gte, s32 *, 0x014) + 0x40;
            M2C_FIELD(gte, s32 *, 0x014) = temp_v0_8;
            if (M2C_FIELD(gte, s32 *, 0x018) < temp_v0_8) {
                var_a2_3 = (void *)3;
                goto block_83;
            }
            goto loop_37;
        }
block_83:
        var_a0_2 = -1;
        temp_v0_9 = M2C_FIELD(gte, s32 *, 0x00C);
        var_v1_2 = (s32 *)(gte + 0x78);
        temp_v0_9 += 0x40;
        M2C_FIELD(gte, s32 *, 0x00C) = temp_v0_9;
        do {
            if (M2C_FIELD(var_v1_2, s32 *, 0x38) > 0) {
                temp_v0_9 = M2C_FIELD(var_v1_2, s32 *, 0x28) - 0x40;
                M2C_FIELD(var_v1_2, s32 *, 0x28) = temp_v0_9;
                if (temp_v0_9 <= 0) {
                    M2C_FIELD(var_v1_2, s32 *, 0x38) = var_a0_2;
                    M2C_FIELD(gte, u16 *, 0x174) = M2C_FIELD(gte, u16 *, 0x174) - 1;
                }
            }
            var_a2_3 -= 1;
            var_v1_2 -= 0x28;
        } while ((s32) var_a2_3 >= 0);
        if (M2C_FIELD(gte, u16 *, 0x174) == 0) {
            goto block_89;
        }
        goto loop_5;
    }
block_89:
    M2C_FIELD(M2C_FIELD(d_80083160, void **, 0), u32 *, 0x8D0) = var_s0;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    {
        u8 *page8007;
        u8 *adbc;
        page8007 = (u8 *)0x80070000;
        ASM_KEEP_NV(page8007);   /* MATCH pin: load-bearing for the whole function shape */
        adbc = page8007 - 0x5244;
        if ((M2C_FIELD(adbc, s16 *, 0x18) == 0xC) && ((u32) (M2C_FIELD(adbc, u16 *, 0x1A) - 0x25) >= 5U) && ((s16) M2C_FIELD(adbc, u16 *, 0x1A) != 0x34)) {
            func_800AD138(M2C_FIELD(gte, s32 *, 0x164));
        }
    }
}
