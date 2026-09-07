#include "common.h"

/* First sub-object header written at arg0+0x0 */
typedef struct S_8004F068_a {
    /*0x00*/ u8  unk00;
    /*0x01*/ u8  unk01;
    /*0x02*/ u8  pad02[2];
    /*0x04*/ s32 unk04;
    /*0x08*/ s32 unk08;
    /*0x0C*/ s32 unk0C;
    /*0x10*/ u8  pad10[8];
} S_8004F068_a;

/* Second sub-object header written at arg0+0x18 */
typedef struct S_8004F068_b {
    /*0x00*/ u8  unk00;
    /*0x01*/ u8  unk01;
    /*0x02*/ u8  pad02[2];
    /*0x04*/ u16 unk04;
    /*0x06*/ u16 unk06;
    /*0x08*/ u8  pad08[4];
} S_8004F068_b;

/* Each is a single hi/lo-addressed word; padded >8B so gcc doesn't use %gp_rel */
typedef struct { s32 v; s32 pad[2]; } S_8004F068_word;
extern S_8004F068_word D_80071678;
extern S_8004F068_word D_8007167C;
extern S_8004F068_word D_80071680;

/* Initializes two adjacent headers with flags and global values, then returns the next field. */
void *func_8004F068(void *cursor)
{
    S_8004F068_a *first_header = (S_8004F068_a *)cursor;
    S_8004F068_b *second_header;
    s32 word_04, word_08, word_0c;

    first_header->unk01 = 0xB0;
    word_08 = D_80071678.v;
    first_header->unk08 = word_08;
    word_04 = D_80071680.v;
    word_0c = D_8007167C.v;
    first_header->unk01 |= 2;
    first_header->unk00 |= 0x61;
    first_header->unk04 = word_04;
    first_header->unk0C = word_0c;

    cursor = (u8 *)cursor + 0x18;
    second_header = (S_8004F068_b *)cursor;
    second_header->unk01 = 0x81;
    second_header->unk04 = 0x20;
    second_header->unk06 = 1;
    second_header->unk00 |= 0x80;

    return (u8 *)second_header + 0xC;
}
