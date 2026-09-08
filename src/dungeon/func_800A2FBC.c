/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

s32 func_8003DE58();
s32 func_80098920();
M2C_UNK func_8009A028();
s32 func_8009B164();
void *func_8009B25C();
M2C_UNK func_800A2B04();
M2C_UNK func_800A7A7C();
M2C_UNK func_800A891C();
M2C_UNK func_800A8CA8();
M2C_UNK func_800A8E20();
M2C_UNK func_800B66C8();
s16 func_800BCB04();
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern M2C_UNK D_80081484;
extern s32 D_800814A0[3];
extern void *D_800814A8;
extern u16 D_80083460[6];
extern u8 D_800DD7DC[];
extern s32 D_800E3540;
extern void *D_800E3D7C[3];

#ifdef NON_MATCHING
#define DUNGEON_FLAGS_PAGE ((s8 *)D_800814A0 - 0x14A0)
#else
#define DUNGEON_FLAGS_PAGE ((s8 *)0x80080000)
#endif


typedef struct S_800A871C_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800A871C_0;   /* temp_v1 in func_800A871C */

typedef struct S_800A871C_1_pre {
    u16 unk_00;
} S_800A871C_1_pre;   /* the 0x2 bytes before r_arg0 in func_800A871C, addressed as r_arg0[-1] */

typedef struct S_800A871C_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    void * unk_90;
    u8 pad_94[0x8];
    s32 * unk_9C;
    s16 unk_A0;
    s16 unk_A2;
    s16 unk_A4;
} S_800A871C_1;   /* r_arg0 in func_800A871C */

typedef struct S_800A871C_2 {
    s16 unk_00;
} S_800A871C_2;   /* &sp18[2] in func_800A871C */

typedef struct S_800A871C_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800A871C_3;   /* r_arg1 in func_800A871C */

typedef struct S_800A871C_4 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x18];
    union { u8 n; volatile u8 v; } unk_24;   /* accessed as both */
    union { u8 n; volatile u8 v; } unk_25;   /* accessed as both */
} S_800A871C_4;   /* r_arg2 in func_800A871C */

typedef struct S_800A871C_5 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800A871C_5;   /* temp_a1 in func_800A871C */

typedef struct S_800A871C_6 {
    s16 unk_00;
} S_800A871C_6;   /* temp_table_y_derived in func_800A871C */

typedef struct S_800A871C_7 {
    u8 unk_00;
} S_800A871C_7;   /* (u8 *)((unsigned long)temp_a0_5 + (unsigned long)temp_table_x_2) in func_800A871C */

typedef struct S_800A871C_8 {
    u8 unk_00;
} S_800A871C_8;   /* temp_a0_6 in func_800A871C */

typedef struct S_800A871C_9 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800A871C_9;   /* temp_a1_2 in func_800A871C */

typedef struct S_800A871C_10 {
    u8 pad_00[0x88];
    u16 unk_88;
} S_800A871C_10;   /* temp_global_814A8 in func_800A871C */

typedef struct S_800A871C_11_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800A871C_11_pre;   /* the 0x14 bytes before temp_v0_5 in func_800A871C, addressed as temp_v0_5[-1] */

typedef struct S_800A871C_11 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800A871C_11;   /* temp_v0_5 in func_800A871C */

typedef struct S_800A871C_12 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800A871C_12;   /* temp_a1_3 in func_800A871C */

typedef struct S_800A871C_13 {
    u8 unk_00;
} S_800A871C_13;   /* (u8 *)((unsigned long)temp_a0_8 + (unsigned long)temp_table_x_3) in func_800A871C */

typedef struct S_800A871C_14 {
    u8 unk_00;
} S_800A871C_14;   /* (u8 *)&D_8006CCE8 + temp_a0_8 in func_800A871C */

typedef struct S_800A871C_15 {
    u8 pad_00[0x3D7C];
    void * unk_3D7C;
} S_800A871C_15;   /* temp_e_page in func_800A871C */

typedef struct S_800A871C_16 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_800A871C_16;   /* temp_flags_page in func_800A871C */

typedef struct S_800A871C_17 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x28];
    s32 unk_48;
} S_800A871C_17;   /* temp_v0_2 in func_800A871C */

typedef struct S_800A871C_18 {
    u8 unk_00;
} S_800A871C_18;   /* (u8 *)((unsigned long)temp_a0_2 + (unsigned long)temp_table_x_4) in func_800A871C */

typedef struct S_800A871C_19 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x5C];
    s16 unk_88;
} S_800A871C_19;   /* (*(void **)((u8 *)temp_s0 + (0x60))) in func_800A871C */

typedef struct S_800A871C_20 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x2];
    s32 ** unk_28;
    void * unk_2C;
} S_800A871C_20;   /* ((S_800A871C_1 *)r_arg0)->unk_90 in func_800A871C */

typedef struct S_800A871C_21 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800A871C_21;   /* ((S_800A871C_1 *)r_arg0)->unk_8C in func_800A871C */

typedef struct S_800A871C_22 {
    u8 pad_00[0x124];
    s32 unk_124;
} S_800A871C_22;   /* ((S_800A871C_15 *)temp_e_page)->unk_3D7C in func_800A871C */

typedef struct S_800A871C_23 {
    s32 unk_00;
} S_800A871C_23;   /* ((S_800A871C_1 *)r_arg0)->unk_9C in func_800A871C */

typedef struct S_800A871C_24 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_800A871C_24;   /* ((S_800A871C_20 *)(((S_800A871C_1 *)r_arg0)->unk_90))->unk_2C in func_800A871C */

typedef struct S_800A871C_25 {
    s32 unk_00;
} S_800A871C_25;   /* **((S_800A871C_20 *)(((S_800A871C_1 *)r_arg0)->unk_90))->unk_28 +
                                ((s32) ((S_800A871C_24 *)(((S_800A871C_20 *)(((S_800A871C_1 *)r_arg0)->unk_90))->unk_2C))->unk_02 * 4) in func_800A871C */

typedef struct S_800A871C_26 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800A871C_26;   /* ((S_800A871C_25 *)(**((S_800A871C_20 *)(((S_800A871C_1 *)r_arg0)->unk_90))->unk_28 +
                                ((s32) ((S_800A871C_24 *)(((S_800A871C_20 *)(((S_800A871C_1 *)r_arg0)->unk_90))->unk_2C))->unk_02 * 4)))->unk_00 in func_800A871C */

void func_800A871C(void *arg0, void *arg1, void *arg2) {
    void *r_arg0 = arg0;
    register void *r_arg1 ASM_REG("$19") = arg1;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register void *incoming_arg2 ASM_REG("$6") = arg2;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    void *r_arg2;
    register void *temp_s0 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u16 sp18[3];
    s16 temp_a0;
    s32 temp_a0_4;
    s16 temp_v0;
    s16 temp_v1_2;
    s16 var_a2;
    s16 var_a2_2;
    s32 *temp_v1;
    s32 temp_a0_2;
    register s32 temp_a0_5 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 temp_a0_8;
    s32 temp_axis_adjusted;
    s32 temp_axis_scaled;
    register s32 temp_v1_3 ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 temp_v1_4;
    u16 temp_a0_7;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u8 *temp_a0_3;
    u8 *temp_a0_6;
    register u8 *temp_table_x_2 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    u8 *temp_table_x_3;
    register u8 *temp_table_x_4 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    S_800A871C_5 *temp_a1;
    S_800A871C_9 *temp_a1_2;
    void *temp_a1_3;
    S_800A871C_17 *temp_v0_2;
    void *temp_v0_5;
    u8 *temp_table_y_hot;
    u8 *temp_table_y_derived;
    s32 temp_tail_result;
    s32 temp_tail_delta;
    u8 *temp_e_page;
    void *temp_global_814A8;
    s32 temp_global_sum;
    s32 temp_global_flags;
    s32 temp_height;

    ASM_KEEP4_NV(r_arg0, r_arg1, r_arg2, incoming_arg2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    temp_s0 = r_arg0;
    r_arg2 = incoming_arg2;
    temp_v1 = (*(s32 **)((u8 *)temp_s0 + (0x9C)));
    if ((temp_v1 == &D_80081484) && (((S_800A871C_0 *)temp_v1)->unk_01 == 0)) {
        (*(s32 **)((u8 *)temp_s0 + (0x9C))) = &D_800E3540;
    }
    temp_v1_2 = ((S_800A871C_1 *)r_arg0)->unk_A0;
    if (temp_v1_2 != 0) {
        if (temp_v1_2 != 1) {
            func_800A8E20();
            return;
        }
        goto block_type1;
    }
    {
        if ((*(s32 *)((u8 *)temp_s0 + (0x1C))) & 0x200000) {
            (*(u16 *)((u8 *)temp_s0 + (0x2A))) = (u16) ((S_800A871C_19 *)((*(void **)((u8 *)temp_s0 + (0x60)))))->unk_2A;
            if (func_8003DE58(
                    ((S_800A871C_26 *)(((S_800A871C_25 *)(**((S_800A871C_20 *)(((S_800A871C_1 *)r_arg0)->unk_90))->unk_28 +
                                ((s32) ((S_800A871C_24 *)(((S_800A871C_20 *)(((S_800A871C_1 *)r_arg0)->unk_90))->unk_2C))->unk_02 * 4)))->unk_00))->unk_04,
                    ((S_800A871C_1 *)r_arg0)->unk_90, sp18, 0) == 0) {
                ((S_800A871C_2 *)(&sp18[2]))->unk_00 = -0x30;
            }
            ((S_800A871C_3 *)r_arg1)->unk_08.at02.v = (s16) (((S_800A871C_21 *)(((S_800A871C_1 *)r_arg0)->unk_8C))->unk_0A + sp18[2]);
            ((S_800A871C_4 *)r_arg2)->unk_24.n = (u8) ((S_800A871C_20 *)(((S_800A871C_1 *)r_arg0)->unk_90))->unk_24;
            ((S_800A871C_4 *)r_arg2)->unk_25.n = (u8) ((S_800A871C_20 *)(((S_800A871C_1 *)r_arg0)->unk_90))->unk_25;
            func_800A2B04(r_arg1, ((S_800A871C_4 *)r_arg2)->unk_24.v, ((S_800A871C_4 *)r_arg2)->unk_25.v);
            ((S_800A871C_1 *)r_arg0)->unk_A0 = (s16) ((u16) ((S_800A871C_1 *)r_arg0)->unk_A0 + 1);
            temp_a1 = (*(void * volatile *)((u8 *)temp_s0 + (0x60)));
            temp_a0_4 = (*(s16 *)((u8 *)temp_s0 + (0x8A)));
            temp_v0_4 = temp_a1->unk_2A;
            (*(s16 *)((u8 *)temp_s0 + (0x6A))) = (s16) temp_v0_4;
            temp_v1_3 = (temp_v0_4 >> 9) & 7;
            if (temp_a0_4 != 0) {
                s16 *temp_table_x = (s16 *)&D_8006CCD8;
                temp_v1_4 = temp_v1_3 * 2;
                temp_table_y_hot = (u8 *)&D_8006CCE8;
                temp_table_y_derived = (u8 *)((unsigned long)temp_v1_4 + (unsigned long)temp_table_y_hot);
                temp_tail_result = func_800BCB04((((((S_800A871C_4 *)r_arg2)->unk_24.n + (*(s16 *)((u8 *)temp_table_x + temp_v1_4) * temp_a0_4)) << 6) + 0x20) & 0xFFE0, (((((S_800A871C_4 *)r_arg2)->unk_25.n + (((S_800A871C_6 *)temp_table_y_derived)->unk_00 * temp_a0_4)) << 6) + 0x20) & 0xFFE0, ((S_800A871C_3 *)r_arg1)->unk_08.at02.v);
                if (temp_tail_result < 0x200) {
                    temp_tail_delta = temp_tail_result - ((S_800A871C_3 *)r_arg1)->unk_08.at02.v;
                    ASM_TAILSLOT_PIN(temp_tail_delta);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    func_800A891C();
                    return;
                }
                ((S_800A871C_3 *)r_arg1)->unk_14 = (s32) ((s32) ((((S_800A871C_19 *)((*(void **)((u8 *)temp_s0 + (0x60)))))->unk_88 - ((S_800A871C_3 *)r_arg1)->unk_08.at02.v) << 0xF) / (s16) (*(u16 *)((u8 *)temp_s0 + (0x8A))));
            }
            temp_table_x_2 = (u8 *)&D_8006CCD8;
            temp_a0_5 = temp_v1_3 * 2;
            ((S_800A871C_4 *)r_arg2)->unk_24.n = (u8) (((S_800A871C_4 *)r_arg2)->unk_24.n + ((S_800A871C_7 *)((u8 *)((unsigned long)temp_a0_5 + (unsigned long)temp_table_x_2)))->unk_00);
            temp_a0_6 = (u8 *)&D_8006CCE8 + temp_a0_5;
            ((S_800A871C_4 *)r_arg2)->unk_25.n = (u8) (((S_800A871C_4 *)r_arg2)->unk_25.n + ((S_800A871C_8 *)temp_a0_6)->unk_00);
            ((S_800A871C_1 *)r_arg0)->unk_A4 = 2;
            return;
        }
        temp_a1_2 = ((S_800A871C_1 *)r_arg0)->unk_90;
        if ((func_8003DE58(temp_a1_2->unk_08, temp_a1_2, sp18, 0) != 0) && ((*(s32 *)((u8 *)temp_s0 + (0x1C))) & 0x80000)) {
            ((S_800A871C_1 *)r_arg0)->unk_A2 = 1;
            ((S_800A871C_3 *)r_arg1)->unk_00.at02.v = (s16) (((S_800A871C_21 *)(((S_800A871C_1 *)r_arg0)->unk_8C))->unk_02 + sp18[0]);
            ((S_800A871C_3 *)r_arg1)->unk_04.at02.v = (s16) (((S_800A871C_21 *)(((S_800A871C_1 *)r_arg0)->unk_8C))->unk_06 + sp18[1]);
            temp_global_sum = ((S_800A871C_21 *)(((S_800A871C_1 *)r_arg0)->unk_8C))->unk_0A + sp18[2];
            temp_global_814A8 = D_800814A8;
            ((S_800A871C_3 *)r_arg1)->unk_08.at02.v = (s16) (temp_global_sum + 8);
            (*(u16 *)((u8 *)temp_s0 + (0x88))) = ((S_800A871C_10 *)temp_global_814A8)->unk_88;
            goto block_A8B54;
        }
        if (((S_800A871C_1 *)r_arg0)->unk_A2 != 0) {
            if ((*(s32 *)((u8 *)temp_s0 + (0x1C))) & 0x80000) {
                temp_e_page = (u8 *)0x800E0000;
                goto block_A8B58;
            }
            {
                temp_v0_5 = (*(void **)((u8 *)temp_s0 + (0x60)));
                temp_table_x_3 = (u8 *)&D_8006CCD8;
                temp_a0_7 = ((S_800A871C_11 *)temp_v0_5)->unk_2A;
                temp_a1_3 = ((S_800A871C_11_pre *)temp_v0_5)[-1].unk_00;
                (*(s16 *)((u8 *)temp_s0 + (0x6A))) = (s16) temp_a0_7;
                temp_a0_8 = (temp_a0_7 >> 8) & 0xE;
                ((S_800A871C_4 *)r_arg2)->unk_24.n = (u8) (((S_800A871C_12 *)temp_a1_3)->unk_24 + ((S_800A871C_13 *)((u8 *)((unsigned long)temp_a0_8 + (unsigned long)temp_table_x_3)))->unk_00);
                ((S_800A871C_4 *)r_arg2)->unk_25.n = (u8) (((S_800A871C_12 *)temp_a1_3)->unk_25 + ((S_800A871C_14 *)((u8 *)&D_8006CCE8 + temp_a0_8))->unk_00);
                func_800A2B04(r_arg1, ((S_800A871C_4 *)r_arg2)->unk_24.v, ((S_800A871C_4 *)r_arg2)->unk_25.v);
                var_a2_2 = func_800BCB04((((S_800A871C_4 *)r_arg2)->unk_24.n << 6) | 0x20, (((S_800A871C_4 *)r_arg2)->unk_25.n << 6) | 0x20, ((S_800A871C_3 *)r_arg1)->unk_08.at02.v);
                if (var_a2_2 >= 0x201) {
                    var_a2_2 = (s16) (u16) ((S_800A871C_3 *)r_arg1)->unk_08.at02.v;
                }
                func_800A7A7C(((S_800A871C_4 *)r_arg2)->unk_24.n, ((S_800A871C_4 *)r_arg2)->unk_25.n, var_a2_2, ((S_800A871C_4 *)r_arg2)->unk_08, ((S_800A871C_1 *)r_arg0)->unk_9C);
                ((S_800A871C_1_pre *)r_arg0)[-1].unk_00 = (u16) (((S_800A871C_1_pre *)r_arg0)[-1].unk_00 | 0x8000);
                temp_global_flags = D_800814A0[0];
                temp_height = ((S_800A871C_3 *)r_arg1)->unk_08.at02.v;
                D_800814A0[0] = (s32) (temp_global_flags | 0x8000);
                ((S_800A871C_3 *)r_arg1)->unk_08.at02.v = func_800BCB04((((S_800A871C_4 *)r_arg2)->unk_24.n << 6) | 0x20, (((S_800A871C_4 *)r_arg2)->unk_25.n << 6) | 0x20, temp_height);
                func_800B66C8(r_arg1);
                func_8009A028(temp_s0);
                return;
                   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                return;
            }
block_A8B54:
            temp_e_page = (u8 *)0x800E0000;
block_A8B58:
            if (((S_800A871C_22 *)(((S_800A871C_15 *)temp_e_page)->unk_3D7C))->unk_124 == 0) {
                void *temp_call_arg = temp_s0;
                register s8 *temp_flags_page ASM_REG("$3") = DUNGEON_FLAGS_PAGE;   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
                ((S_800A871C_1_pre *)r_arg0)[-1].unk_00 = (u16) (((S_800A871C_1_pre *)r_arg0)[-1].unk_00 | 0x8000);
                temp_global_flags = ((S_800A871C_16 *)temp_flags_page)->unk_14A0;
                temp_global_flags |= 0x8000;
                func_8009A028((((S_800A871C_16 *)temp_flags_page)->unk_14A0 = temp_global_flags, temp_call_arg));
                return;
            }
            goto block_49;
        }
        return;
    }
block_type1:
    temp_a0 = ((S_800A871C_1 *)r_arg0)->unk_A4;
    if (temp_a0 != 0) {
        temp_axis_scaled = ((S_800A871C_4 *)r_arg2)->unk_24.n;
        temp_axis_adjusted = ((S_800A871C_3 *)r_arg1)->unk_00.at02.v;
        temp_axis_scaled <<= 6;
        temp_axis_adjusted -= 0x20;
        ((S_800A871C_3 *)r_arg1)->unk_0C = (s32) (((temp_axis_scaled - temp_axis_adjusted) << 0x10) / temp_a0);
        temp_axis_scaled = ((S_800A871C_4 *)r_arg2)->unk_25.n;
        temp_axis_adjusted = ((S_800A871C_3 *)r_arg1)->unk_04.at02.v;
        temp_axis_adjusted -= 0x20;
        temp_axis_scaled <<= 6;
        ((S_800A871C_3 *)r_arg1)->unk_10 = (s32) (((temp_axis_scaled - temp_axis_adjusted) << 0x10) / (s16) ((S_800A871C_1 *)r_arg0)->unk_A4);
    }
    temp_v0 = (u16) ((S_800A871C_1 *)r_arg0)->unk_A4 - 1;
    ((S_800A871C_1 *)r_arg0)->unk_A4 = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        goto block_49;
    }
    temp_v0_2 = func_8009B25C(temp_s0, ((S_800A871C_4 *)r_arg2)->unk_24.n, ((S_800A871C_4 *)r_arg2)->unk_25.n, (*(s16 *)((u8 *)temp_s0 + (0x88))));
    if (temp_v0_2 != NULL) {
        if ((temp_v0_2->unk_13 == 0x1F) && !(temp_v0_2->unk_1C & 0x228) && (D_800DD7DC[0] != 0)) {
            temp_v0_2->unk_14 = (s32) (temp_v0_2->unk_14 | 0x800000);
            temp_v0_2->unk_48 = ((S_800A871C_23 *)(((S_800A871C_1 *)r_arg0)->unk_9C))->unk_00;
            func_800A8CA8(temp_v0_2);
            return;
        }
        if (func_80098920(temp_v0_2, ((S_800A871C_1 *)r_arg0)->unk_9C, 0xD, temp_s0) != 0) {
            ASM_KEEP(temp_s0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            ((S_800A871C_1_pre *)r_arg0)[-1].unk_00 = (u16) (((S_800A871C_1_pre *)r_arg0)[-1].unk_00 | 0x8000);
            D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
            func_8009A028(temp_s0);
            D_80083460[5] = (u16) (D_80083460[5] - 1);
            return;
        }
    }
    if ((func_8009B164((*(s16 *)((u8 *)temp_s0 + (0x6A))), r_arg1, r_arg2) << 0x10) != 0) {
        temp_v0_3 = (*(u16 *)((u8 *)temp_s0 + (0x8A))) - 1;
        (*(u16 *)((u8 *)temp_s0 + (0x8A))) = temp_v0_3;
        if ((temp_v0_3 << 0x10) > 0) {
            func_800A2B04(r_arg1, ((S_800A871C_4 *)r_arg2)->unk_24.n, ((S_800A871C_4 *)r_arg2)->unk_25.n);
            temp_table_x_4 = (u8 *)&D_8006CCD8;
            temp_a0_2 = ((u16) (*(s16 *)((u8 *)temp_s0 + (0x6A))) >> 8) & 0xE;
            ((S_800A871C_4 *)r_arg2)->unk_24.n = (u8) (((S_800A871C_4 *)r_arg2)->unk_24.n + ((S_800A871C_18 *)((u8 *)((unsigned long)temp_a0_2 + (unsigned long)temp_table_x_4)))->unk_00);
            temp_a0_3 = (u8 *)&D_8006CCE8 + temp_a0_2;
            ((S_800A871C_4 *)r_arg2)->unk_25.n = (u8) (((S_800A871C_4 *)r_arg2)->unk_25.n + *temp_a0_3);
            ((S_800A871C_1 *)r_arg0)->unk_A4 = 2;
            func_800A8E20();
            return;
        }
    }
    var_a2 = func_800BCB04((((S_800A871C_4 *)r_arg2)->unk_24.n << 6) | 0x20, (((S_800A871C_4 *)r_arg2)->unk_25.n << 6) | 0x20, ((S_800A871C_3 *)r_arg1)->unk_08.at02.v);
    if (var_a2 >= 0x201) {
        var_a2 = (s16) (u16) ((S_800A871C_3 *)r_arg1)->unk_08.at02.v;
    }
    func_800A7A7C(((S_800A871C_4 *)r_arg2)->unk_24.n, ((S_800A871C_4 *)r_arg2)->unk_25.n, var_a2, ((S_800A871C_4 *)r_arg2)->unk_08, ((S_800A871C_1 *)r_arg0)->unk_9C);
    ((S_800A871C_1_pre *)r_arg0)[-1].unk_00 = (u16) (((S_800A871C_1_pre *)r_arg0)[-1].unk_00 | 0x8000);
    D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
            func_8009A028(temp_s0);
    D_80083460[5] = (u16) (D_80083460[5] - 1);
block_49:
    ((S_800A871C_3 *)r_arg1)->unk_00.at00.v = (s32) (((S_800A871C_3 *)r_arg1)->unk_00.at00.v + ((S_800A871C_3 *)r_arg1)->unk_0C);
    ((S_800A871C_3 *)r_arg1)->unk_04.at00.v = (s32) (((S_800A871C_3 *)r_arg1)->unk_04.at00.v + ((S_800A871C_3 *)r_arg1)->unk_10);
    ((S_800A871C_3 *)r_arg1)->unk_08.at00.v = (s32) (((S_800A871C_3 *)r_arg1)->unk_08.at00.v + ((S_800A871C_3 *)r_arg1)->unk_14);
}
