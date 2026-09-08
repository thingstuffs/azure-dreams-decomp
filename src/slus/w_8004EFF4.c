#include "common.h"

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

/* Initializes two records and returns a pointer at offset 0x24 from the original base. */
void *func_8004EFF4(S_8004EFF4 *record)
{
    s32 initial_04;
    s32 initial_0c;

    record->unk01 = 0xB0;
    record->unk08 = D_8007166C[0];
    initial_04 = D_80071674[0];
    initial_0c = D_80071670[0];
    record->unk01 = record->unk01 | 2;
    record->unk00 = record->unk00 | 0x60;
    record->unk04 = initial_04;
    record->unk0C = initial_0c;
    record = (S_8004EFF4 *)((u8 *)record + 0x18);
    ((S_8004EFF4_sub *)record)->unk18_01 = 0x81;
    ((S_8004EFF4_sub *)record)->unk18_04 = 0x20;
    ((S_8004EFF4_sub *)record)->unk18_06 = 1;
    ((S_8004EFF4_sub *)record)->unk18_00 = ((S_8004EFF4_sub *)record)->unk18_00 | 0x80;
    return (u8 *)record + 0xC;
}
