#include "common.h"
#include "records/Rec_func_80025D28_arg0.h"


typedef struct S_80025D28_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80025D28_1;   /* arg1 in func_80025D28 */

typedef struct S_80025D28_2 {
    u8 pad_00[0xD];
    u8 unk_0D;
} S_80025D28_2;   /* arg2 in func_80025D28 */



extern s32 func_800644B8();
extern s32 func_80064584();
extern u8 D_80027452[16];
extern s32 D_800814A0;

void func_80025D28(void *arg0, void *arg1, void *arg2) {
    s32 temp_s1;
    s32 temp_s1_raw;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_prod;
    s32 temp_prod_2;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_s0_4;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    u16 temp_v0_2;
    u8 temp_v0;

    temp_s1_raw = ((Rec_func_80025D28_arg0 *)arg0)->unk_38;
    temp_s1 = (s16)(temp_s1_raw << 6);
    *(u16 *)D_80027452 = *(u16 *)D_80027452 + 1;
    temp_s0 = func_800644B8(temp_s1);
    ((S_80025D28_1 *)arg1)->unk_00 = (((Rec_func_80025D28_arg0 *)arg0)->unk_1C << 0x10) +
        ((s32)(temp_s0 * func_80064584(((Rec_func_80025D28_arg0 *)arg0)->unk_36 + 0x400) * ((Rec_func_80025D28_arg0 *)arg0)->unk_3E) >> 7);
    temp_s0_2 = func_800644B8(temp_s1);
    ((S_80025D28_1 *)arg1)->unk_04 = (((Rec_func_80025D28_arg0 *)arg0)->unk_1E << 0x10) +
        ((s32)(temp_s0_2 * func_800644B8(((Rec_func_80025D28_arg0 *)arg0)->unk_36 + 0x400) * ((Rec_func_80025D28_arg0 *)arg0)->unk_3E) >> 7);
    ((S_80025D28_1 *)arg1)->unk_08 = (((Rec_func_80025D28_arg0 *)arg0)->unk_20 << 0x10) +
        ((func_80064584(temp_s1) * ((Rec_func_80025D28_arg0 *)arg0)->unk_3E) << 5);
    temp_s2 = func_800644B8(temp_s1);
    temp_s0_3 = func_80064584(((Rec_func_80025D28_arg0 *)arg0)->unk_36 + 0x400);
    temp_v0_3 = func_80064584(((Rec_func_80025D28_arg0 *)arg0)->unk_36 + 0x800);
    temp_prod = temp_s2 * temp_s0_3;
    temp_prod *= ((Rec_func_80025D28_arg0 *)arg0)->unk_3E;
    ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
    temp_lo = temp_v0_3 * ((Rec_func_80025D28_arg0 *)arg0)->unk_40;
    ((S_80025D28_1 *)arg1)->unk_0C = (((Rec_func_80025D28_arg0 *)arg0)->unk_1C << 0x10) +
        (temp_prod >> 7) + (temp_lo << 6);
    temp_s2_2 = func_800644B8(temp_s1, temp_lo);
    temp_s0_4 = func_800644B8(((Rec_func_80025D28_arg0 *)arg0)->unk_36 + 0x400);
    temp_v0_4 = func_800644B8(((Rec_func_80025D28_arg0 *)arg0)->unk_36 + 0x800);
    temp_prod_2 = temp_s2_2 * temp_s0_4;
    temp_prod_2 *= ((Rec_func_80025D28_arg0 *)arg0)->unk_3E;
    ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
    temp_lo_2 = temp_v0_4 * ((Rec_func_80025D28_arg0 *)arg0)->unk_40;
    ((S_80025D28_1 *)arg1)->unk_10 = (((Rec_func_80025D28_arg0 *)arg0)->unk_1E << 0x10) +
        (temp_prod_2 >> 7) + (temp_lo_2 << 6);
    ((S_80025D28_1 *)arg1)->unk_14 = (((Rec_func_80025D28_arg0 *)arg0)->unk_20 << 0x10) +
        ((func_80064584(temp_s1, temp_lo_2) * ((Rec_func_80025D28_arg0 *)arg0)->unk_3E) << 5);
    ((Rec_func_80025D28_arg0 *)arg0)->unk_40 = (u16)((Rec_func_80025D28_arg0 *)arg0)->unk_40 + 2;
    ((Rec_func_80025D28_arg0 *)arg0)->unk_38 = (u16)((Rec_func_80025D28_arg0 *)arg0)->unk_38 + 1;
    temp_v0 = ((S_80025D28_2 *)arg2)->unk_0D;
    ((S_80025D28_2 *)arg2)->unk_0D = temp_v0 - (temp_v0 >> 3);
    temp_v0_2 = ((Rec_func_80025D28_arg0 *)arg0)->unk_30 - 1;
    ((Rec_func_80025D28_arg0 *)arg0)->unk_30 = temp_v0_2;
    if ((temp_v0_2 << 0x10) <= 0) {
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
    ((Rec_func_80025D28_arg0 *)arg0)->unk_34 = ((Rec_func_80025D28_arg0 *)arg0)->unk_34 + 1;
}

/* MECHANISM: Natural long-lived arguments and results produce the retail 0x30 frame and s5/s4/s3/s2/s1/s0 roles.
   A short raw signed-load local selects lh before the shift/truncation while preserving temp_s1 in s1.
   Zero-operand scheduling barriers after both chained products reproduce retail multiply/mflo emission order. */
