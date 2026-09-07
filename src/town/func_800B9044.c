#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Template0;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Template1;

typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
} Instance0;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Instance1;

typedef struct {
    s32 unk0;
    Instance0 *unk4;
    Instance1 *unk8;
} Owner;

typedef union {
    s32 value;
} StackArg;

extern Template0 D_8002E5D8;
extern Template1 D_8002E5E8;

void func_800B67A4(Owner *a0, Template0 *a1, Instance1 *a2,
                   s32 arg3, StackArg arg4, StackArg arg5) {
    s32 y = arg4.value;
    s32 z = arg5.value;
    Template0 *src0 = &D_8002E5D8;
    Template1 *src1 = &D_8002E5E8;
    s32 *tmp;

    a1->unk0 = src0->unk0;
    tmp = &src1->unk0;
    a1->unk4 = src0->unk4;
    a1->unk8 = src0->unk8;
    a1->unkC = src0->unkC;

    ((Template1 *)a2)->unk0 = *tmp;
    ((Template1 *)a2)->unk4 = src1->unk4;
    ((Template1 *)a2)->unk8 = src1->unk8;
    

    a0->unk4 = (Instance0 *)a1;
    a0->unk8 = a2;
    a0->unk0 = 0;

    a0->unk4->unk8 = arg3;
    a0->unk4->unkA = y;
    a0->unk4->unkC = z;
    a0->unk4->unkF = 4;
}
