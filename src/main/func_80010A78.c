#include "common.h"

/* Entity-init: copy two global templates (D_8002E5D8->*a1, D_8002E5E8->*a2), link them
   into a0, then patch 4 fields of *a1 with hardcoded/scaled defaults. Same shape as
   func_8004EEFC, but the unkA field is derived from arg3 instead of a fixed constant. */
typedef struct S_8002E5D8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} S_8002E5D8;

typedef struct S_8002E5E8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} S_8002E5E8;

extern S_8002E5D8 D_8002E5D8;
extern S_8002E5E8 D_8002E5E8;

typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
} S_80010A78_a1;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} S_80010A78_a2;

typedef struct {
    s32 unk0;
    S_80010A78_a1 *unk4;
    S_80010A78_a2 *unk8;
} S_80010A78_a0;

void func_80023A78(S_80010A78_a0 *a0, S_8002E5D8 *a1, S_80010A78_a2 *a2, s32 arg3) {
    S_8002E5D8 *src0 = &D_8002E5D8;
    S_8002E5E8 *src1 = &D_8002E5E8;
    s32 *tmp;

    a1->unk0 = src0->unk0;
    tmp = &src1->unk0;
    a1->unk4 = src0->unk4;
    a1->unk8 = src0->unk8;
    a1->unkC = src0->unkC;

    ((S_8002E5E8 *)a2)->unk0 = *tmp;
    ((S_8002E5E8 *)a2)->unk4 = src1->unk4;
    ((S_8002E5E8 *)a2)->unk8 = src1->unk8;

    a0->unk4 = (S_80010A78_a1 *)a1;
    a0->unk8 = a2;
    a0->unk0 = 0;

    a0->unk4->unk8 = -0xA0;
    a0->unk4->unkA = (arg3 * 0x18) - 0x78;
    a0->unk4->unkC = 0x200;
    a0->unk4->unkF = 4;
}
