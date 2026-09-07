#include "common.h"

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} Inner;

typedef struct {
    s32 unk0;
    Inner *unk4;
} Result;

typedef struct {
    s32 index;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 word10;
    s32 word14;
    s32 unk18;
    s32 unk1C;
    s32 word20;
    s32 unk24;
    s32 unk28;
    s32 word2C;
} Source;

typedef struct {
    s32 *dst0;
    s32 **dst4;
    s32 **dst8;
    Result *dstC;
} Destinations;

extern s32 D_80029508[];
extern void func_80026370(Destinations *, s32);
extern s32 func_8004DC14(s32, s32);

void func_80026878(Source *src, Destinations *dst)
{
    *dst->dst0 = D_80029508[src->word10];
    *dst->dst4 = &src->word2C;
    func_80026370(dst, 0);
    *dst->dst8 = &src->word20;
    dst->dstC->unk0 = func_8004DC14(src->word14, 0);
    dst->dstC->unk4->unk8 = 0x68;
    dst->dstC->unk4->unkA = 0x88;
}
