#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} S_8002E5D8;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} S_8002E5E8;

extern S_8002E5D8 D_8002E5D8;
extern S_8002E5E8 D_8002E5E8;

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
} PatchRecord;

typedef struct {
    s32 unk0;
    PatchRecord *unk4;
    S_8002E5E8 *unk8;
} Owner;

void func_80025D9C(void *unused, Owner *arg1, S_8002E5D8 *arg2,
                   S_8002E5E8 *arg3) {
    S_8002E5D8 *src0 = &D_8002E5D8;
    S_8002E5E8 *src1 = &D_8002E5E8;
    s32 *tmp;

    arg2->unk0 = src0->unk0;
    tmp = &src1->unk0;
    arg2->unk4 = src0->unk4;
    arg2->unk8 = src0->unk8;
    arg2->unkC = src0->unkC;

    arg3->unk0 = *tmp;
    arg3->unk4 = src1->unk4;
    arg3->unk8 = src1->unk8;

    arg1->unk4 = (PatchRecord *)arg2;
    arg1->unk8 = arg3;
    arg1->unk0 = 0;

    arg1->unk4->unk8 = 0x2C;
    arg1->unk4->unkA = -8;
    arg1->unk4->unkC = 0x200;
    arg1->unk4->unk6 = 0;
    arg1->unk4->unkF = 4;
}
