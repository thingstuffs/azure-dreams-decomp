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

/* Initializes two adjacent sub-structures inside the object at arg0, setting
 * flag bytes and copying three global words in, then returns a pointer to a
 * third field just past the second sub-structure. */
void *func_8004F068(void *arg0)
{
    S_8004F068_a *a = (S_8004F068_a *)arg0;
    S_8004F068_b *b;
    s32 t4, t8, tc;

    a->unk01 = 0xB0;
    t8 = D_80071678.v;
    a->unk08 = t8;
    t4 = D_80071680.v;
    tc = D_8007167C.v;
    a->unk01 |= 2;
    a->unk00 |= 0x61;
    a->unk04 = t4;
    a->unk0C = tc;

    arg0 = (u8 *)arg0 + 0x18;
    b = (S_8004F068_b *)arg0;
    b->unk01 = 0x81;
    b->unk04 = 0x20;
    b->unk06 = 1;
    b->unk00 |= 0x80;

    return (u8 *)b + 0xC;
}
