#include "common.h"

/* Initializes a struct's two sub-records (base record + record at +0x18)
 * and returns a pointer partway into the third slot (+0x18+0xC). */
extern s32 D_8007166C[];
extern s32 D_80071670[];
extern s32 D_80071674[];

typedef struct S_8004EFF4 {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 pad02[2];
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ u8 pad10[8];
} S_8004EFF4;

typedef struct S_8004EFF4_sub {
    /* 0x00 */ u8 unk18_00;
    /* 0x01 */ u8 unk18_01;
    /* 0x02 */ u8 pad02[2];
    /* 0x04 */ s16 unk18_04;
    /* 0x06 */ s16 unk18_06;
} S_8004EFF4_sub;

void *func_8004EFF4(S_8004EFF4 *a0)
{
    s32 temp_a1;
    s32 temp_a2;

    a0->unk01 = 0xB0;
    a0->unk08 = D_8007166C[0];
    temp_a1 = D_80071674[0];
    temp_a2 = D_80071670[0];
    a0->unk01 = a0->unk01 | 2;
    a0->unk00 = a0->unk00 | 0x60;
    a0->unk04 = temp_a1;
    a0->unk0C = temp_a2;
    a0 = (S_8004EFF4 *)((u8 *)a0 + 0x18);
    ((S_8004EFF4_sub *)a0)->unk18_01 = 0x81;
    ((S_8004EFF4_sub *)a0)->unk18_04 = 0x20;
    ((S_8004EFF4_sub *)a0)->unk18_06 = 1;
    ((S_8004EFF4_sub *)a0)->unk18_00 = ((S_8004EFF4_sub *)a0)->unk18_00 | 0x80;
    return (u8 *)a0 + 0xC;
}
