#include "common.h"

/* Globals: single scalar values read via %hi/%lo. Declared as arrays (>8B)
 * to force hi/lo codegen for this single-use load. D_80071664 is volatile:
 * this defeats the compiler's tendency to fuse the address computation and
 * the load into one scheduled unit, matching retail's split (the %hi
 * computation is hoisted early to fill an unrelated load's delay slot,
 * while the %lo-folded load itself stays at its later point of use). */
extern s32 D_80071660[4];
extern volatile u32 D_80071664[4];
extern s32 D_80071668[4];

typedef struct S_8004EF90_sub {
    u8 unk0;
    u8 unk1;
    u8 pad2[2];
    s16 unk4;
    s16 unk6;
    u8 pad8[4];
} S_8004EF90_sub;

typedef struct S_8004EF90 {
    u8 unk0;
    u8 unk1;
    u8 pad2[2];
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 pad10[8];
    S_8004EF90_sub sub;
} S_8004EF90;

/* Initialize the object header and embedded record, then return the following anchor. */
void *func_8004EF90(void *cursor)
{
    S_8004EF90 *object = (S_8004EF90 *)cursor;
    S_8004EF90_sub *sub_header;
    s32 sub_init_value;
    s32 initial_word_4;
    s32 initial_word_c;

    object->unk1 = 0xB0;
    object->unk8 = D_80071660[0];
    sub_init_value = 0x81;
    initial_word_4 = D_80071668[0];
    initial_word_c = D_80071664[0];
    object->unk1 = 2 | object->unk1;
    object->unk4 = initial_word_4;
    object->unkC = initial_word_c;

    cursor = (u8 *)cursor + 0x18;
    sub_header = (S_8004EF90_sub *)cursor;
    sub_header->unk1 = sub_init_value;
    sub_header->unk4 = 0x20;
    sub_init_value = 0;
    sub_header->unk6 = sub_init_value;
    sub_header->unk0 = sub_header->unk0 | 0x80;

    return (u8 *)cursor + 0xC;
}
