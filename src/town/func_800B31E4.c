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

void func_800B0944(TownOwner *arg0, TownPartA *arg1, TownPartB *arg2) {
    s32 *src1 = D_8002E5D8;
    s32 *src2 = D_8002E5E8;
    s32 first2;

    ((s32 *)arg1)[0] = D_8002E5D8[0];
    ((s32 *)arg1)[1] = src1[1];
    ((s32 *)arg1)[2] = src1[2];
    first2 = D_8002E5E8[0];
    ((s32 *)arg1)[3] = src1[3];
    ((s32 *)arg2)[0] = first2;
    ((s32 *)arg2)[1] = src2[1];
    ((s32 *)arg2)[2] = src2[2];
    arg0->partA = arg1;
    arg0->partB = arg2;
    arg0->unk0 = 0;
    arg0->partA->unk8 = 0;
    arg0->partA->unkA = -0x6C;
    arg0->partA->unkC = 0x200;
    arg0->partA->unkF = 4;
    arg0->partA->unk6 = 0;
    arg0->partB->unk8 = 0x30;
}
