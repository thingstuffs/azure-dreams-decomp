/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80046884();     /* extern */
s32 func_80046C20(); /* extern */
M2C_UNK func_80064624();                    /* extern */
M2C_UNK func_80064D20();                      /* extern */
M2C_UNK func_80064D50();                      /* extern */
M2C_UNK func_800AD138();                         /* extern */
extern u8 D_8006ADBC[];
extern u8 D_80083160[];
extern s32 D_800D1548[3];
extern u8 D_800D1554[9];

typedef struct S_func_800AED64_1 {
    void * unk_00;
    u8 pad_04[0x16];
    s16 unk_1A;
    u8 pad_1C[0x2];
    s16 unk_1E;
    u8 pad_20[0x88];
    s32 unk_A8;
    u8 pad_AC[0x130];
    void * unk_1DC;
} S_func_800AED64_1;

typedef struct S_func_800AED64_2 {
    u8 pad_00[0x4];
    s32 unk_04;
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0x4];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
} S_func_800AED64_2;

typedef struct S_func_800AED64_3 {
    u8 pad_00[0x84];
    s32 unk_84;
    s32 unk_88;
} S_func_800AED64_3;

typedef struct S_func_800AED64_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    union {
        s32 s32;
        u16 u16;
    } unk_14;
    s32 unk_18;
    u8 pad_1C[0xA0];
    s32 unk_BC;
    s32 unk_C0;
    u8 pad_C4[0x4];
    s32 unk_C8;
    u8 pad_CC[0x8];
    s32 unk_D4;
    u8 pad_D8[0x4];
    s32 unk_DC;
    s32 unk_E0;
    union {
        s16 s16;
        u16 u16;
    } unk_E4;
    u8 pad_E6[0x2];
    s32 unk_E8;
    s16 unk_EC;
    u8 pad_EE[0x2];
    s32 unk_F0;
    s16 unk_F4;
    u8 pad_F6[0x2];
    s32 unk_F8;
    s16 unk_FC;
    u8 pad_FE[0x12];
    s32 unk_110;
    s32 unk_114;
    s32 unk_118;
    s32 unk_11C;
    s32 unk_120;
    s32 unk_124;
    s32 unk_128;
    union {
        s32 s32;
        u16 u16;
    } unk_12C;
    u8 pad_130[0x4];
    s32 unk_134;
    s32 unk_138;
    u8 pad_13C[0x8];
    s32 unk_144;
    u8 pad_148[0x4];
    s32 unk_14C;
    u8 pad_150[0x14];
    s32 unk_164;
    union {
        s32 s32;
        u16 u16;
        struct {
            u8 pad_168[0x2];
            u16 unk_16A;
        } at_16A;
    } unk_168;
    union {
        s32 s32;
        struct {
            u8 pad_16C[0x2];
            u8 unk_16E;
        } at_16E;
        struct {
            u8 pad_16C[0x3];
            u8 unk_16F;
        } at_16F;
    } unk_16C;
    s32 unk_170;
    u16 unk_174;
    u16 unk_176;
    u16 unk_178;
    u8 pad_17A[0x2];
    s32 unk_17C;
} S_func_800AED64_4;

typedef struct S_func_800AED64_5 {
    u8 pad_00[0x3180];
    s32 unk_3180;
    u8 unk_3184;
    u8 unk_3185;
} S_func_800AED64_5;

typedef struct S_func_800AED64_6 {
    u8 pad_00[0x8D0];
    u32 unk_8D0;
} S_func_800AED64_6;

typedef struct S_func_800AED64_7 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
    s32 unk_2C;
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
} S_func_800AED64_7;

typedef struct S_func_800AED64_8 {
    u16 unk_00;
} S_func_800AED64_8;

typedef struct S_func_800AED64_9 {
    u8 pad_00[0x3];
    s8 unk_03;
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
    u8 pad_18[0x4];
    u16 unk_1C;
    u8 pad_1E[0x6];
    u16 unk_24;
} S_func_800AED64_9;

typedef struct S_func_800AED64_10 {
    u8 pad_00[0x4];
    s32 unk_04;
    u16 unk_08;
    u16 unk_0A;
} S_func_800AED64_10;

typedef struct S_func_800AED64_11 {
    s32 unk_00;
} S_func_800AED64_11;

typedef struct S_func_800AED64_12 {
    void * unk_00;
} S_func_800AED64_12;

typedef struct S_func_800AED64_13 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    union {
        s32 s32;
        struct {
            u8 pad_14[0x2];
            u8 unk_16;
        } at_16;
        struct {
            u8 pad_14[0x3];
            s8 unk_17;
        } at_17;
    } unk_14;
} S_func_800AED64_13;

typedef struct S_func_800AED64_14 {
    u8 pad_00[0x3];
    s8 unk_03;
    union {
        s32 s32;
        struct {
            u8 pad_04[0x3];
            u8 unk_07;
        } at_07;
    } unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    u16 unk_1C;
    u8 pad_1E[0x2];
    void * unk_20;
    u16 unk_24;
} S_func_800AED64_14;

typedef struct S_func_800AED64_15 {
    s32 unk_00;
    u16 unk_04;
} S_func_800AED64_15;

typedef struct S_func_800AED64_16 {
    s32 unk_00;
    s16 unk_04;
} S_func_800AED64_16;

typedef struct S_func_800AED64_17 {
    u8 pad_00[0x18];
    s16 unk_18;
    u16 unk_1A;
} S_func_800AED64_17;

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
    register s32 temp_v1_8 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register s32 tail_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 var_a0_2;
    M2C_UNK * var_a0_3;
    register s32 var_a2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 var_a2_2;
    s8 *var_s6;
    s32 var_v1;
    u16 temp_v1_10;
    u32 temp_v0_5;
    M2C_UNK * var_s0;
    void *temp_s0;
    register S_func_800AED64_2 *temp_s5 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    S_func_800AED64_10 *temp_t6;
    S_func_800AED64_7 *var_a0;
    S_func_800AED64_7 *var_a1;
    register S_func_800AED64_13 *var_a2_3 ASM_REG("$6"); /* MATCH: the polygon loop keeps its cursor in a2, sharing the outer loop counter register. */
    void *var_a3;
    void *var_t0;
    S_func_800AED64_7 *var_v1_2;
    S_func_800AED64_7 *inner_p;
    register s32 inner_add ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 inner_sub ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 row_limit;
    register void *call_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    void *call_a1;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *call_a2;   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    S_func_800AED64_6 *call_a3;
    u32 tag_low_mask;
    u32 tag_high_mask;
    s32 one;
    S_func_800AED64_4 *gte;
    register void *gte_input ASM_REG("$13");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register S_func_800AED64_1 *d_80083160 ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    {
        register u8 *page8008 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        page8008 = (u8 *)0x80080000;
        ASM_KEEP_NV(page8008);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        d_80083160 = page8008 + 0x3160;
    }
    ASM_KEEP_NV(d_80083160);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    temp_s5 = (u8 *)d_80083160 + 0x1DC;
    var_s6 = d_80083160->unk_1DC;
    temp_s2 = temp_s5->unk_08;
    temp_s3 = temp_s5->unk_0C;
    func_80064D50((u8 *)d_80083160 + 0x70);
    {
        S_func_800AED64_3 *base18;
        base18 = (u8 *)d_80083160 + 0x18;
        func_80064624(base18->unk_84, base18->unk_88);
    }
    gte = (s8 *)0x1F800000;
    ASM_KEEP_NV(gte);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    func_80064D20((u8 *)d_80083160 + 0x50);
    if (D_800D1554[0] != 0) {
        d_80083160->unk_1A = -0xB8;
        tail_v0 = 0x1DA;
    } else {
        ASM_KEEP(d_80083160);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        d_80083160->unk_1A = -0x88;
        tail_v0 = 0x1AA;
    }
    d_80083160->unk_1E = tail_v0;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    temp_s0 = (u8 *)d_80083160 + 0x20;
    func_80046884((u8 *)d_80083160 + 0x18, temp_s0, 0);
    call_a0 = temp_s0;
    call_a1 = (void *) ((u32) gte | 0x1C);
    init_v0 = d_80083160->unk_A8;
    call_a2 = (void *) ((u32) gte | 0x174);
    gte->unk_00 = init_v0;
    init_v1 = d_80083160->unk_00;
    temp_a3 = temp_s5->unk_14;
    temp_t0 = temp_s5->unk_16;
    init_t1 = temp_s5->unk_18;
    init_t2 = temp_s5->unk_1A;
    {
        S_func_800AED64_5 *page;
        page = (u8 *)0x80010000;
        init_t3 = page->unk_3180;
        init_t4 = page->unk_3184;
        init_byte = page->unk_3185;
    }
    init_v1 += 0xB0;
    gte->unk_124 = (s32) temp_a3;
    ((volatile S_func_800AED64_4 *)(gte))->unk_178 = init_byte;
    gte->unk_BC = init_v1;
    gte->unk_128 = (s32) temp_t0;
    gte->unk_114 = 0x40 << gte->unk_124;
    gte->unk_11C = (s32) init_t1;
    gte->unk_120 = (s32) init_t2;
    gte->unk_110 = init_t3;
    gte->unk_176 = init_t4;
    call_a3 = d_80083160->unk_00;
    gte->unk_118 = 0x40 << gte->unk_128;
    var_s0 = call_a3->unk_8D0;
    gte->unk_14C = 0xFFFF;
    gte->unk_174 = 4;
    gte->unk_164 = (u8 *) var_s0 + 0xCCCC;
    gte->unk_0C = (s16) func_80046C20(call_a0, call_a1, call_a2, call_a3);
    if (gte->unk_174 != 0) {
        one = 1;
        gte_input = (u8 *)gte + 0xE0;
        temp_t6 = D_800D1548;
        tag_low_mask = 0xFFFFFF;
        tag_high_mask = 0xFF000000;
loop_5:
        var_a2 = 3;
        var_a0 = (s32 *)((u8 *)gte + 0x78);
        do {
            if (var_a0->unk_38 == 0) {
                temp_v1_8 = var_a0->unk_34;
                tail_v0 = gte->unk_0C;
                if (tail_v0 >= temp_v1_8) {
                    var_a0->unk_38 = one;
                }
            }
            var_a2 -= 1;
            var_a0 = (S_func_800AED64_7 *)((u8 *)var_a0 - 0x28);
        } while (var_a2 >= 0);
        var_a2_2 = 3;
        var_a1 = (s32 *)((u8 *)gte + 0x78);
        gte->unk_14.s32 = 0x7FFF;
        gte->unk_18 = -0x7FFF;
        do {
            if (var_a1->unk_38 > 0) {
                temp_v1 = var_a1->unk_1C;
                gte->unk_08 = temp_v1;
                if (temp_v1 < gte->unk_14.s32) {
                    gte->unk_14.s32 = temp_v1;
                }
                temp_v1_2 = gte->unk_08;
                if (gte->unk_18 < temp_v1_2) {
                    gte->unk_18 = temp_v1_2;
                }
                temp_v1_3 = var_a1->unk_2C + var_a1->unk_24;
                var_a1->unk_2C = temp_v1_3;
                if (temp_v1_3 >= 0) {
                    inner_p = var_a1;
                    inner_add = var_a1->unk_30;
                    inner_sub = var_a1->unk_20;
loop_18:
                    tail_v0 = inner_p->unk_1C;
                    temp_v1_8 = inner_p->unk_3C;
                    tail_v0 += inner_add;
                    inner_p->unk_1C = tail_v0;
                    tail_v0 = inner_p->unk_2C;
                    temp_v1_8 -= 0x40;
                    inner_p->unk_3C = temp_v1_8;
                    tail_v0 -= inner_sub;
                    inner_p->unk_2C = tail_v0;
                    if (temp_v1_8 > 0) {
                        if (tail_v0 >= 0) {
                            goto loop_18;
                        }
                    }
                }
                temp_v1_5 = var_a1->unk_1C;
                gte->unk_08 = temp_v1_5;
                if (temp_v1_5 < gte->unk_14.s32) {
                    gte->unk_14.s32 = temp_v1_5;
                }
                temp_v1_6 = gte->unk_08;
                if (gte->unk_18 < temp_v1_6) {
                    gte->unk_18 = temp_v1_6;
                }
            }
            var_a2_2 -= 1;
            var_a1 = (S_func_800AED64_7 *)((u8 *)var_a1 - 0x28);
        } while (var_a2_2 >= 0);
        gte->unk_14.s32 = (gte->unk_14.s32 - 0x20) & ~0x3F;
        var_a0_2 = ((volatile S_func_800AED64_4 *)gte)->unk_14.s32;
        gte->unk_18 = (gte->unk_18 + 0x20) & ~0x3F;
        if (var_a0_2 < 0) {
            var_a0_2 += 0x3F;
        }
        var_v1 = gte->unk_0C;
        gte->unk_134 = var_a0_2 >> 6;
        if (var_v1 < 0) {
            var_v1 += 0x3F;
        }
        temp_v1_7 = var_v1 >> 6;
        gte->unk_138 = temp_v1_7;
        if (temp_v1_7 < 0) {
            gte->unk_138 = 0;
        } else {
            row_limit = gte->unk_120;
            if (temp_v1_7 >= row_limit) {
                tail_v0 = row_limit << gte->unk_124;
            } else {
                tail_v0 = temp_v1_7 << gte->unk_124;
            }
            gte->unk_138 = tail_v0;
        }
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        temp_v1_8 = gte->unk_14.s32;
        tail_v0 = gte->unk_18;
        var_a2_3 = (void *)3;
        if (tail_v0 >= temp_v1_8) {
            var_t0 = (s8 *) var_s0 + 0x20;
loop_37:
            temp_v1_8 = gte->unk_134;
            if (temp_v1_8 < 0) {
                tail_v0 = gte->unk_138;
                temp_v1_8 &= 3;
            } else {
                var_a0_3 = gte->unk_11C;
                if (temp_v1_8 >= (s32) var_a0_3) {
                    tail_v0 = gte->unk_138;
                    temp_v1_8 &= 3;
                    tail_v0 += (s32) var_a0_3;
                    tail_v0 += temp_v1_8;
                    tail_v0 -= 3;
                    goto store_column;
                }
                tail_v0 = gte->unk_138;
            }
            tail_v0 += temp_v1_8;
store_column:
            gte->unk_144 = tail_v0;
            temp_v0_3 = ((S_func_800AED64_8 *)(var_s6 + (((volatile S_func_800AED64_4 *)(gte))->unk_144 * 2)))->unk_00 & 0x3FFF;
            gte->unk_C0 = temp_v0_3;
            if (temp_v0_3 != 0) {
                temp_v0_4 = ((S_func_800AED64_8 *)(var_s6 + (gte->unk_144 * 2)))->unk_00 & 0xC000;
                gte->unk_17C = temp_v0_4;
                if (temp_v0_4 != 0) {
                    gte->unk_FC = 0;
                    gte->unk_F4 = 0;
                    gte->unk_EC = 0;
                    gte->unk_E4.s16 = 0;
                    gte->unk_E0 = (u16) gte->unk_14.s32 | (gte->unk_0C << 0x10);
                    gte->unk_E8 = ((((volatile S_func_800AED64_4 *)(gte))->unk_14.u16 + 0x40) & 0xFFFF) | (gte->unk_0C << 0x10);
                    gte->unk_F0 = (u16) gte->unk_14.s32 | ((gte->unk_0C + 0x40) << 0x10);
                    gte->unk_F8 = ((((volatile S_func_800AED64_4 *)(gte))->unk_14.u16 + 0x40) & 0xFFFF) | ((gte->unk_0C + 0x40) << 0x10);
                    gte_ldv3(gte_input, (u8 *)gte + 0xE8, (u8 *)gte + 0xF0);
                    ((S_func_800AED64_9 *)((u8 *)var_t0 - 0x20))->unk_04 = 0x2C404040;
                    gte_rtpt_nn();
                    gte_avsz3();
                    gte_stotz((u8 *)gte + 0xC8);
                    gte_stsxy3_g3(var_s0);
                    gte_ldv0((u8 *)gte + 0xF8);
                    ((S_func_800AED64_9 *)((u8 *)var_t0 - 0x20))->unk_0C = (s32) D_800D1548[0];
                    gte_rtps_nn();
                    gte_stsxy(var_t0);
                    ((S_func_800AED64_9 *)((u8 *)var_t0 - 0x20))->unk_14 = (s32) temp_t6->unk_04;
                    ((S_func_800AED64_9 *)((u8 *)var_t0 - 0x20))->unk_1C = (u16) temp_t6->unk_08;
                    ((S_func_800AED64_9 *)((u8 *)var_t0 - 0x20))->unk_24 = (u16) temp_t6->unk_0A;
                    gte_stszotz((u8 *)gte + 0xD4);
                    call_a0 = (void *)gte->unk_D4;
                    tail_v0 = gte->unk_C8;
                    temp_v1_8 = tail_v0 << 1;
                    tail_v0 += temp_v1_8;
                    tail_v0 += (s32)call_a0;
                    tail_v0 += 3;
                    tail_v0 >>= 2;
                    tail_v0 += 4;
                    gte->unk_C8 = tail_v0;
                    if ((u32)tail_v0 >= 0x200U) {
                        gte->unk_C8 = 0x1FF;
                    }
                    ((S_func_800AED64_9 *)((u8 *)var_t0 - 0x20))->unk_03 = 9;
                    var_t0 += 0x28;
                    var_a0_3 = (s32) var_s0 & tag_low_mask;
                    *var_s0 = (s32) ((*var_s0 & tag_high_mask) | (((S_func_800AED64_11 *)((s8 *)gte->unk_BC + (gte->unk_C8 * 4)))->unk_00 & tag_low_mask));
                    temp_v1_9 = (gte->unk_C8 * 4) + gte->unk_BC;
                    var_s0 = (s32 *)((s8 *)var_s0 + 0x28);
                    *temp_v1_9 = (*temp_v1_9 & tag_high_mask) | (s32) var_a0_3;
                }
                c0idx = gte->unk_C0;
                ASM_USE_NV(c0idx);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                var_a3 = (s8 *)var_s0 + 4;
                ASM_KEEP(var_a3);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                gte->unk_12C.s32 = 0;
                var_a2_3 = ((S_func_800AED64_12 *)((s8 *)temp_s5->unk_04 + (c0idx * 4)))->unk_00;
                for (;;) {
                    if (var_a2_3->unk_0C != 0) {
                        tail_v0 = var_a2_3->unk_10;
                        call_a0 = (void *) (u32) gte->unk_14.u16;
                        gte->unk_170 = tail_v0;
                        tail_v0 = var_a2_3->unk_00;
                        temp_v1_8 = var_a2_3->unk_14.s32;
                        tail_v0 <<= 3;
                        tail_v0 += (s32) temp_s2;
                        gte->unk_16C.s32 = temp_v1_8;
                        tail_v0 = ((S_func_800AED64_15 *)((void *) tail_v0))->unk_00;
                        temp_v1_8 = gte->unk_12C.u16;
                        gte->unk_168.s32 = tail_v0;
                        tail_v0 = var_a2_3->unk_00;
                        call_a1 = (void *) (u32) gte->unk_168.u16;
                        tail_v0 <<= 3;
                        tail_v0 += (s32) temp_s2;
                        call_a0 = (void *) ((u32) call_a0 + (u32) call_a1);
                        tail_v0 = ((S_func_800AED64_15 *)((void *) tail_v0))->unk_04;
                        call_a0 = (void *) ((u32) call_a0 & 0xFFFF);
                        tail_v0 -= temp_v1_8;
                        gte->unk_E4.s16 = tail_v0;
                        tail_v0 = gte->unk_168.at_16A.unk_16A;
                        temp_v1_8 = gte->unk_0C;
                        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                        ASM_KEEP_NV(tail_v0);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                        tail_v0 = (s32) (tail_v0 << 0x10) >> 0x10;
                        temp_v1_8 += tail_v0;
                        temp_v1_8 <<= 0x10;
                        tail_v0 = var_a2_3->unk_02;
                        call_a0 = (void *) ((u32) call_a0 | (u32) temp_v1_8);
                        gte->unk_E0 = (s32) call_a0;
                        call_a0 = (void *) (u32) gte->unk_14.u16;
                        temp_v1_8 = gte->unk_12C.u16;
                        tail_v0 <<= 3;
                        tail_v0 += (s32) temp_s2;
                        tail_v0 = ((S_func_800AED64_15 *)((void *) tail_v0))->unk_00;
                        gte->unk_168.s32 = tail_v0;
                        tail_v0 = var_a2_3->unk_02;
                        call_a1 = (void *) (u32) gte->unk_168.u16;
                        tail_v0 <<= 3;
                        tail_v0 += (s32) temp_s2;
                        call_a0 = (void *) ((u32) call_a0 + (u32) call_a1);
                        tail_v0 = ((S_func_800AED64_15 *)((void *) tail_v0))->unk_04;
                        call_a0 = (void *) ((u32) call_a0 & 0xFFFF);
                        tail_v0 -= temp_v1_8;
                        gte->unk_EC = tail_v0;
                        tail_v0 = gte->unk_168.at_16A.unk_16A;
                        temp_v1_8 = gte->unk_0C;
                        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                        ASM_KEEP_NV(tail_v0);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                        tail_v0 = (s32) (tail_v0 << 0x10) >> 0x10;
                        temp_v1_8 += tail_v0;
                        temp_v1_8 <<= 0x10;
                        tail_v0 = var_a2_3->unk_04;
                        call_a0 = (void *) ((u32) call_a0 | (u32) temp_v1_8);
                        gte->unk_E8 = (s32) call_a0;
                        call_a0 = (void *) (u32) gte->unk_14.u16;
                        tail_v0 <<= 3;
                        tail_v0 += (s32) temp_s2;
                        tail_v0 = ((S_func_800AED64_15 *)((void *) tail_v0))->unk_00;
                        gte->unk_168.s32 = tail_v0;
                        tail_v0 = gte->unk_168.u16;
                        temp_v1_8 = ((volatile S_func_800AED64_4 *)(gte))->unk_168.at_16A.unk_16A;
                        call_a0 = (void *) ((u32) call_a0 + (u32) tail_v0);
                        call_a0 = (void *) ((u32) call_a0 & 0xFFFF);
                        temp_v1_8 <<= 0x10;
                        tail_v0 = gte->unk_0C;
                        temp_v1_8 >>= 0x10;
                        tail_v0 += temp_v1_8;
                        tail_v0 <<= 0x10;
                        call_a0 = (void *) ((u32) call_a0 | (u32) tail_v0);
                        gte->unk_F0 = (s32) call_a0;
                        tail_v0 = var_a2_3->unk_04;
                        tail_v0 <<= 3;
                        tail_v0 += (s32) temp_s2;
                        temp_v1_8 = ((S_func_800AED64_15 *)((void *) tail_v0))->unk_04;
                        tail_v0 = gte->unk_12C.u16;
                        temp_v1_8 -= tail_v0;
                        gte->unk_F4 = temp_v1_8;
                        gte_ldv3(gte_input, (u8 *)gte + 0xE8, (u8 *)gte + 0xF0);
                        gte_rtpt();
                        gte_nclip();
                        gte_stopz((u8 *)gte + 0xDC);
                        if (gte->unk_DC >= 0) {
                            tail_v0 = var_a2_3->unk_06;
                            tail_v0 <<= 3;
                            tail_v0 += (s32) temp_s2;
                            temp_v1_8 = ((S_func_800AED64_15 *)((void *) tail_v0))->unk_04;
                            tail_v0 = gte->unk_12C.u16;
                            temp_v1_8 -= tail_v0;
                            gte->unk_FC = temp_v1_8;
                            gte_stsxy3_g3(var_s0);
                            gte_avsz3();
                            gte_stotz((u8 *)gte + 0xC8);
                            temp_v1_10 = (u16) gte->unk_170;
                            if (gte->unk_14C != temp_v1_10) {
                                gte->unk_14C = (s32) temp_v1_10;
                                gte_ldrgb(gte);
                                gte_ldv0(temp_s3 + (temp_v1_10 * 8));
                                gte_nccs();
                                gte_strgb((u8 *)gte + 4);
                            }
                            tail_v0 = var_a2_3->unk_06;
                            call_a0 = (void *) (u32) gte->unk_14.u16;
                            tail_v0 <<= 3;
                            tail_v0 += (s32) temp_s2;
                            tail_v0 = ((S_func_800AED64_15 *)((void *) tail_v0))->unk_00;
                            gte->unk_168.s32 = tail_v0;
                            tail_v0 = gte->unk_168.u16;
                            temp_v1_8 = ((volatile S_func_800AED64_4 *)(gte))->unk_168.at_16A.unk_16A;
                            call_a0 = (void *) ((u32) call_a0 + (u32) tail_v0);
                            call_a0 = (void *) ((u32) call_a0 & 0xFFFF);
                            temp_v1_8 <<= 0x10;
                            tail_v0 = gte->unk_0C;
                            temp_v1_8 >>= 0x10;
                            tail_v0 += temp_v1_8;
                            tail_v0 <<= 0x10;
                            call_a0 = (void *) ((u32) call_a0 | (u32) tail_v0);
                            gte->unk_F8 = (s32) call_a0;
                            gte_ldv0((u8 *)gte + 0xF8);
                            ((S_func_800AED64_14 *)((u8 *)var_a3 - 0x4))->unk_0C = (s32) var_a2_3->unk_08;
                            gte_rtps_nn();
                            ((S_func_800AED64_14 *)((u8 *)var_a3 - 0x4))->unk_14 = (s32) var_a2_3->unk_0C;
                            ((S_func_800AED64_14 *)((u8 *)var_a3 - 0x4))->unk_1C = (u16) *(s32 *)((u8 *)(u8 *)gte + 0x172);
                            ((S_func_800AED64_14 *)((u8 *)var_a3 - 0x4))->unk_24 = (u16) gte->unk_16C.s32;
                            gte_stsxy(var_t0);
                            gte_stszotz((u8 *)gte + 0xD4);
                            call_a0 = (void *)gte->unk_D4;
                            tail_v0 = gte->unk_C8;
                            temp_v1_8 = tail_v0 << 1;
                            tail_v0 += temp_v1_8;
                            tail_v0 += (s32)call_a0;
                            tail_v0 += 3;
                            tail_v0 >>= 2;
                            gte->unk_C8 = tail_v0;
                            if ((u32) tail_v0 >= 0x200U) {
                                gte->unk_C8 = 0x1FF;
                            }
                            if ((((s32) gte->unk_C8 < 0x1C1) || ((s32) (gte->unk_E4.u16 << 0x10) >= 0) || ((tail_v0 = gte->unk_14C, tail_v0 <<= 3, call_a0 = (void *)(tail_v0 + (s32)temp_s3), var_a0_3 = call_a0, (((S_func_800AED64_16 *)(var_a0_3))->unk_04 < 0)) && !(((S_func_800AED64_16 *)(var_a0_3))->unk_00 & 0x0FFF0FFF))) && ((u32) gte->unk_C8 < 0x200U)) {
                                ((S_func_800AED64_14 *)((u8 *)var_a3 - 0x4))->unk_03 = 9;
                                ((S_func_800AED64_14 *)((u8 *)var_a3 - 0x4))->unk_04.s32 = (s32) gte->unk_04;
                                if (gte->unk_16C.at_16F.unk_16F & 1) {
                                    ((S_func_800AED64_14 *)((u8 *)var_a3 - 0x4))->unk_04.at_07.unk_07 |= 2;
                                } else {
                                    tail_v0 = 0xC000;
                                    temp_v1_8 = gte->unk_17C & 0xC000;
                                    if (temp_v1_8 == tail_v0) {
                                        tail_v0 = ((S_func_800AED64_14 *)((u8 *)var_a3 - 0x4))->unk_10;
                                        temp_v1_8 = ((S_func_800AED64_14 *)((u8 *)var_a3 - 0x4))->unk_18;
                                        call_a0 = ((S_func_800AED64_14 *)((u8 *)var_a3 - 0x4))->unk_20;
                                        var_t0 += 0x28;
                                        ((S_func_800AED64_14 *)((u8 *)var_a3 - 0x4))->unk_0C = tail_v0;
                                        ((S_func_800AED64_14 *)((u8 *)var_a3 - 0x4))->unk_10 = temp_v1_8;
                                        ((S_func_800AED64_14 *)((u8 *)var_a3 - 0x4))->unk_14 = (s32) call_a0;
                                        temp_v1_8 = gte->unk_110;
                                        tail_v0 = 5;
                                        ((S_func_800AED64_14 *)((u8 *)var_a3 - 0x4))->unk_03 = tail_v0;
                                        ((S_func_800AED64_14 *)((u8 *)var_a3 - 0x4))->unk_04.s32 = temp_v1_8;
                                        var_a3 += 0x28;
                                        tail_v0 = gte->unk_C8;
                                        temp_v1_8 = gte->unk_BC;
                                        tail_v0 <<= 2;
                                        tail_v0 += temp_v1_8;
                                        temp_v1_8 = *var_s0;
                                        tail_v0 = ((S_func_800AED64_11 *)((void *)tail_v0))->unk_00;
                                        temp_v1_8 &= tag_high_mask;
                                        tail_v0 &= tag_low_mask;
                                        temp_v1_8 |= tail_v0;
                                        *var_s0 = temp_v1_8;
                                        call_a0 = (void *)(gte->unk_C8 * 4);
                                        tail_v0 = gte->unk_BC;
                                        call_a0 = (void *)((s32)call_a0 + tail_v0);
                                        tail_v0 = (s32) var_s0 & tag_low_mask;
                                        temp_v1_8 = ((S_func_800AED64_11 *)(call_a0))->unk_00;
                                        var_s0 = (s32 *)((s8 *)var_s0 + 0x28);
                                        temp_v1_8 &= tag_high_mask;
                                        temp_v1_8 |= tail_v0;
                                        ((S_func_800AED64_11 *)(call_a0))->unk_00 = temp_v1_8;
                                        ((S_func_800AED64_14 *)((u8 *)var_a3 - 0x4))->unk_03 = one;
                                        temp_v1_8 = gte->unk_176;
                                        tail_v0 = 0xE1000000;
                                        temp_v1_8 &= 0x9FF;
                                        temp_v1_8 |= tail_v0;
                                        ((S_func_800AED64_14 *)((u8 *)var_a3 - 0x4))->unk_04.s32 = temp_v1_8;
                                    }
                                }
                                var_a3 += 0x28;
                                ASM_KEEP(var_a3);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                                var_t0 += 0x28;
                                tail_v0 = gte->unk_C8;
                                temp_v1_8 = gte->unk_BC;
                                tail_v0 <<= 2;
                                tail_v0 += temp_v1_8;
                                temp_v1_8 = *var_s0;
                                tail_v0 = ((S_func_800AED64_11 *)((void *)tail_v0))->unk_00;
                                temp_v1_8 &= tag_high_mask;
                                tail_v0 &= tag_low_mask;
                                temp_v1_8 |= tail_v0;
                                *var_s0 = temp_v1_8;
                                call_a0 = (void *)(gte->unk_C8 * 4);
                                tail_v0 = gte->unk_BC;
                                call_a0 = (void *)((s32)call_a0 + tail_v0);
                                temp_v1_8 = ((S_func_800AED64_11 *)(call_a0))->unk_00;
                                tail_v0 = (s32) var_s0 & tag_low_mask;
                                var_s0 = (s32 *)((s8 *)var_s0 + 0x28);
                                temp_v1_8 &= tag_high_mask;
                                temp_v1_8 |= tail_v0;
                                ((S_func_800AED64_11 *)(call_a0))->unk_00 = temp_v1_8;
                                temp_v1_8 = gte->unk_16C.at_16E.unk_16E;
                                if ((temp_v1_8 & 0xF) == one) {
                                    tail_v0 = gte->unk_16C.at_16F.unk_16F;
                                    tail_v0 <<= 0x18;
                                    if (tail_v0 >= 0) {
                                        temp_v1_8 = (u32) temp_v1_8 >> 4;
                                        tail_v0 = temp_v1_8 * 3;
                                        tail_v0 *= 8;
                                        tail_v0 += 0x18;
                                        var_a2_3 = (s8 *) (u8 *)var_a2_3 + tail_v0;
                                        continue;
                                    }
                                    goto block_80;
                                }
                                goto tail_aca88_18;
                            }
                            goto block_80;
                        }
                        if (((S_func_800AED64_16 *)((((u16) gte->unk_170 * 8) + temp_s3)))->unk_04 < 0) {
                            if (gte->unk_16C.at_16E.unk_16E == one) {
                                tail_v0 = (s32) gte->unk_16C.at_16F.unk_16F << 0x18;
                                goto check_polygon_end;
                            }
                            goto tail_aca88_18;
                        }
                        temp_v1_8 = gte->unk_16C.at_16E.unk_16E;
                        if (temp_v1_8 & 0xF0) {
                            goto tail_aca88_scaled;
                        }
                        tail_v0 = gte->unk_16C.at_16F.unk_16F;
                        tail_v0 <<= 0x18;
                        if (tail_v0 >= 0) {
tail_aca88_scaled:
                            temp_v1_8 &= 0xF;
                            tail_v0 = temp_v1_8 * 3;
                            tail_v0 *= 8;
                            var_a2_3 = (s8 *) (u8 *)var_a2_3 + tail_v0;
                            continue;
                        }
                        goto block_80;
                    }
                    if (var_a2_3->unk_14.at_16.unk_16 != one) {
                        goto tail_aca88_18;
                    }
                    tail_v0 = var_a2_3->unk_14.at_17.unk_17;
check_polygon_end:
                    if (tail_v0 >= 0) {
tail_aca88_18:
                        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                        var_a2_3 = (s8 *) (u8 *)var_a2_3 + 0x18;
                        continue;
                    }
                    break;
                }
block_80:
                if ((u32) gte->unk_164 >= var_s0) {
                    goto block_81;
                }
                goto block_89;
            }
block_81:
            gte->unk_134 += 1;
            temp_v0_8 = gte->unk_14.s32 + 0x40;
            gte->unk_14.s32 = temp_v0_8;
            if (gte->unk_18 < temp_v0_8) {
                var_a2_3 = (void *)3;
                goto block_83;
            }
            goto loop_37;
        }
block_83:
        var_a0_2 = -1;
        temp_v0_9 = gte->unk_0C;
        var_v1_2 = (s32 *)((u8 *)gte + 0x78);
        temp_v0_9 += 0x40;
        gte->unk_0C = temp_v0_9;
        do {
            if (var_v1_2->unk_38 > 0) {
                temp_v0_9 = var_v1_2->unk_28 - 0x40;
                var_v1_2->unk_28 = temp_v0_9;
                if (temp_v0_9 <= 0) {
                    var_v1_2->unk_38 = var_a0_2;
                    gte->unk_174 = gte->unk_174 - 1;
                }
            }
            var_a2_3 = (S_func_800AED64_13 *)((u8 *)var_a2_3 - 1);
            var_v1_2 = (S_func_800AED64_7 *)((u8 *)var_v1_2 - 0x28);
        } while ((s32) var_a2_3 >= 0);
        if (gte->unk_174 == 0) {
            goto block_89;
        }
        goto loop_5;
    }
block_89:
    ((S_func_800AED64_6 *)(d_80083160->unk_00))->unk_8D0 = var_s0;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    {
        u8 *page8007;
        S_func_800AED64_17 *adbc;
        page8007 = (u8 *)0x80070000;
        ASM_KEEP_NV(page8007);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        adbc = page8007 - 0x5244;
        if ((adbc->unk_18 == 0xC) && ((u32) (adbc->unk_1A - 0x25) >= 5U) && ((s16) adbc->unk_1A != 0x34)) {
            func_800AD138(gte->unk_164);
        }
    }
}
