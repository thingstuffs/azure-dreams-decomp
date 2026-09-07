#include "common.h"

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s8 unkE;
    s8 unkF;
} TownPartA;

typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
} TownPartB;

typedef struct {
    s32 unk0;
    TownPartA *partA;
    TownPartB *partB;
} TownOwner;

extern s32 D_8002E5D8[4];
extern s32 D_8002E5E8[3];

/* Initialize and attach both town parts, then set the owner and part defaults. */
void func_800B0944(TownOwner *owner, TownPartA *part_a, TownPartB *part_b) {
    s32 *defaults_a = D_8002E5D8;
    s32 *defaults_b = D_8002E5E8;
    s32 first_b_word;

    ((s32 *)part_a)[0] = D_8002E5D8[0];
    ((s32 *)part_a)[1] = defaults_a[1];
    ((s32 *)part_a)[2] = defaults_a[2];
    first_b_word = D_8002E5E8[0];
    ((s32 *)part_a)[3] = defaults_a[3];
    ((s32 *)part_b)[0] = first_b_word;
    ((s32 *)part_b)[1] = defaults_b[1];
    ((s32 *)part_b)[2] = defaults_b[2];
    owner->partA = part_a;
    owner->partB = part_b;
    owner->unk0 = 0;
    owner->partA->unk8 = 0;
    owner->partA->unkA = -0x6C;
    owner->partA->unkC = 0x200;
    owner->partA->unkF = 4;
    owner->partA->unk6 = 0;
    owner->partB->unk8 = 0x30;
}
