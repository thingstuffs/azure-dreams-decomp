#include "common.h"
#include "slus.h"
#include "slus/data.h"

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

/* Initialize the header and embedded record with global defaults and flags, then return the next address. */
void *func_8004EFF4(S_8004EFF4 *record)
{
    s32 initial_word_4;
    s32 initial_word_c;

    record->unk01 = 0xB0;
    record->unk08 = object_header_b_default_word_08[0];
    initial_word_4 = object_header_b_default_word_04[0];
    initial_word_c = object_header_b_default_word_0c[0];
    record->unk01 = record->unk01 | 2;
    record->unk00 = record->unk00 | 0x60;
    record->unk04 = initial_word_4;
    record->unk0C = initial_word_c;
    record = (S_8004EFF4 *)((u8 *)record + 0x18);
    ((S_8004EFF4_sub *)record)->unk18_01 = 0x81;
    ((S_8004EFF4_sub *)record)->unk18_04 = 0x20;
    ((S_8004EFF4_sub *)record)->unk18_06 = 1;
    ((S_8004EFF4_sub *)record)->unk18_00 = ((S_8004EFF4_sub *)record)->unk18_00 | 0x80;
    return &record->unk0C;
}
