#include "common.h"

/* Resets 6 slot objects reachable through a0 (which itself slides by 4 bytes
 * per iteration): zeroes the unk4-chain's halfword field, and sets the
 * unk28-chain's halfword to 0x1E and both chains' RGB-ish bytes to 0x58
 * (looks like a "reset color/highlight to default grey" pass over 6 slots). */
/* Leaf record: RGB-ish triplet at offset 0, plus a 16-bit field at offset 8. */
typedef struct S_8004FFF4_Leaf {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 pad3[5];
    s16 unk8;
} S_8004FFF4_Leaf;

/* Mid-level indirection object: a pointer to the leaf record at offset 4. */
typedef struct S_8004FFF4_Mid {
    u8 pad0[4];
    S_8004FFF4_Leaf *unk4;
} S_8004FFF4_Mid;

/* Outer per-slot view: two independent mid-object pointers, at offsets 4 and
 * 0x28. a0 slides by 4 bytes per iteration, so successive iterations read an
 * overlapping array-of-pointers region starting at those two offsets. */
typedef struct S_8004FFF4_Outer {
    u8 pad0[4];
    S_8004FFF4_Mid *unk4;
    u8 pad8[0x28 - 8];
    S_8004FFF4_Mid *unk28;
} S_8004FFF4_Outer;

void func_8004FFF4(void *arg0)
{
    s32 i;
    void *a0;

    a0 = arg0;
    i = 0;
    do {
        ((S_8004FFF4_Outer *)a0)->unk4->unk4->unk8 = 0;
        ((S_8004FFF4_Outer *)a0)->unk28->unk4->unk8 = 0x1E;
        ((S_8004FFF4_Outer *)a0)->unk28->unk4->unk0 = 0x58;
        ((S_8004FFF4_Outer *)a0)->unk28->unk4->unk1 = 0x58;
        ((S_8004FFF4_Outer *)a0)->unk28->unk4->unk2 = 0x58;
        ((S_8004FFF4_Outer *)a0)->unk4->unk4->unk0 = 0x58;
        ((S_8004FFF4_Outer *)a0)->unk4->unk4->unk1 = 0x58;
        i += 1;
        ((S_8004FFF4_Outer *)a0)->unk4->unk4->unk2 = 0x58;
        a0 = (u8 *)a0 + 4;
    } while (i < 6);
}
