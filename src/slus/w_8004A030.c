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

/* Initializes four object sub-blocks with position offsets and fixed or header-derived values. */
void func_8004A030(S_8004A030 *object, s32 x, s32 y, s16 extent)
{
    S_8004A030_Sub *block;
    s16 x_offset, y_offset;

    block = (S_8004A030_Sub *)((u8 *)object + 0x20);
    x_offset = (s16)(x - 0xA0);
    y_offset = (s16)(y - 0x80);
    object->unk30 = 0;
    block->unkC = 0x200;
    block->unk8 = x_offset;
    block->unkA = y_offset;
    block->unkF = 4;

    block = (S_8004A030_Sub *)((u8 *)object + 0x40);
    object->unk50 = object->unk1C;
    block->unk8 = 0xC;
    block->unkA = 0xE;

    block = (S_8004A030_Sub *)((u8 *)object + 0x60);
    object->unk70 = object->unk14;
    block->unk8 = extent / 2;
    block->unkA = 8;

    block = (S_8004A030_Sub *)((u8 *)object + 0x80);
    object->unk90 = object->unk18;
    block->unk8 = 0x94;
    block->unkA = 0x81;
}
