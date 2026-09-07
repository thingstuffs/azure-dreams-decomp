#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Template16;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Template12;

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
} Instance16;

typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
} Instance12;

typedef struct {
    s32 unk0;
    Instance16 *unk4;
    Instance12 *unk8;
} Owner;

extern Template16 D_8002E5D8;
extern Template12 D_8002E5E8;

void func_800B3688(Owner *a0, Template16 *a1, Instance12 *a2) {
    Template16 *src0 = &D_8002E5D8;
    Template12 *src1 = &D_8002E5E8;
    s32 *tmp;

    a1->unk0 = src0->unk0;
    tmp = &src1->unk0;
    a1->unk4 = src0->unk4;
    a1->unk8 = src0->unk8;
    a1->unkC = src0->unkC;

    ((Template12 *)a2)->unk0 = *tmp;
    ((Template12 *)a2)->unk4 = src1->unk4;
    ((Template12 *)a2)->unk8 = src1->unk8;

    a0->unk4 = (Instance16 *)a1;
    a0->unk8 = a2;
    a0->unk0 = 0;

    a0->unk4->unk8 = -60;
    a0->unk4->unkA = -92;
    a0->unk4->unkC = 0x200;
    a0->unk4->unk6 = 0;
    a0->unk8->unk8 = 0x30;
    a0->unk4->unkF = 4;
}
