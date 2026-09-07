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

extern Template0 D_8002E5D8;
extern Template1 D_8002E5E8;

typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
} Record0;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s32 unk8;
} Record1;

typedef struct {
    s32 unk0;
    Record0 *unk4;
    Record1 *unk8;
} Header;

void func_80028050(void *arg0, Header *arg1, Template0 *arg2, Record1 *arg3) {
    Template0 *src0 = &D_8002E5D8;
    Template1 *src1 = &D_8002E5E8;
    s32 *tmp;

    arg2->unk0 = src0->unk0;
    tmp = &src1->unk0;
    arg2->unk4 = src0->unk4;
    arg2->unk8 = src0->unk8;
    arg2->unkC = src0->unkC;

    ((Template1 *)arg3)->unk0 = *tmp;
    ((Template1 *)arg3)->unk4 = src1->unk4;
    ((Template1 *)arg3)->unk8 = src1->unk8;

    arg1->unk4 = (Record0 *)arg2;
    arg1->unk8 = arg3;
    arg1->unk0 = 0;

    arg1->unk4->unk8 = -0x58;
    arg1->unk4->unkA = -0x40;
    arg1->unk4->unkC = 0x200;
    arg1->unk8->unk2 = 0x400;
    arg1->unk8->unk6 = -0x50;
    arg1->unk4->unkF = 4;
}
