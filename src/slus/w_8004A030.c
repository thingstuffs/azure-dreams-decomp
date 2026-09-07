#include "common.h"

/* Small sub-block type overlaid at offsets 0x20/0x40/0x60/0x80 of S_8004A030;
 * only the +0x8/+0xA/+0xC/+0xF fields (relative) are ever touched here. */
typedef struct {
    u8 pad0[8];
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 padE;
    u8 unkF;
} S_8004A030_Sub;

typedef struct {
    u8 pad00[0x14];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    u8 pad20[0x10];
    /* 0x30 */ s32 unk30;
    u8 pad34[0x1C];
    /* 0x50 */ s32 unk50;
    u8 pad54[0x1C];
    /* 0x70 */ s32 unk70;
    u8 pad74[0x1C];
    /* 0x90 */ s32 unk90;
} S_8004A030;

/* Initializes four 0x20-byte sub-blocks embedded in the object at arg0
 * (an effect/actor's animation-slot table). Block 0 gets a position offset
 * (arg1,arg2) plus a fixed mode (0x200/4) and its own counter zeroed;
 * blocks 1-3 each copy one of the object's own header words into a shared
 * field and set a fixed +0x8/+0xA pair, except block 2 whose +0x8 value is
 * derived from arg3/2 (signed, rounded toward zero). */
void func_8004A030(S_8004A030 *arg0, s32 arg1, s32 arg2, s16 arg3)
{
    S_8004A030_Sub *v1;
    s16 t1, t2;

    v1 = (S_8004A030_Sub *)((u8 *)arg0 + 0x20);
    t1 = (s16)(arg1 - 0xA0);
    t2 = (s16)(arg2 - 0x80);
    arg0->unk30 = 0;
    v1->unkC = 0x200;
    v1->unk8 = t1;
    v1->unkA = t2;
    v1->unkF = 4;

    v1 = (S_8004A030_Sub *)((u8 *)arg0 + 0x40);
    arg0->unk50 = arg0->unk1C;
    v1->unk8 = 0xC;
    v1->unkA = 0xE;

    v1 = (S_8004A030_Sub *)((u8 *)arg0 + 0x60);
    arg0->unk70 = arg0->unk14;
    v1->unk8 = arg3 / 2;
    v1->unkA = 8;

    v1 = (S_8004A030_Sub *)((u8 *)arg0 + 0x80);
    arg0->unk90 = arg0->unk18;
    v1->unk8 = 0x94;
    v1->unkA = 0x81;
}
