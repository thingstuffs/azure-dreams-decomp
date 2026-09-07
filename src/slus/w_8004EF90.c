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

/* Initializes an object at a0: sets a type/flag byte, copies three global
 * values into fields 4/8/C, then initializes a sub-structure at offset
 * 0x18, and returns a pointer to offset 0xC of that sub-structure. */
void *func_8004EF90(void *a0)
{
    S_8004EF90 *hdr = (S_8004EF90 *)a0;
    S_8004EF90_sub *sub;
    s32 unk1_val;
    s32 unk4_val;
    s32 unkC_val;

    hdr->unk1 = 0xB0;
    hdr->unk8 = D_80071660[0];
    unk1_val = 0x81;
    unk4_val = D_80071668[0];
    unkC_val = D_80071664[0];
    hdr->unk1 = 2 | hdr->unk1;
    hdr->unk4 = unk4_val;
    hdr->unkC = unkC_val;

    a0 = (u8 *)a0 + 0x18;
    sub = (S_8004EF90_sub *)a0;
    sub->unk1 = unk1_val;
    sub->unk4 = 0x20;
    unk1_val = 0;
    sub->unk6 = unk1_val;
    sub->unk0 = sub->unk0 | 0x80;

    return (u8 *)a0 + 0xC;
}
