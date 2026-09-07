#include "common.h"

typedef struct {
    u32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} PatchRecord;

typedef struct {
    void *unk0;
    PatchRecord *unk4;
} Owner;

typedef struct {
    u8 pad0[0x74];
    u8 *unk74;
} Source;

extern u8 D_80078C10[9];
extern u8 D_800789B8[9];
extern u8 D_8007795C[9];
extern u8 D_80029474[9];

extern void func_80025888(Owner **, s32);
extern void func_80025C6C(void *);
extern void *func_8004DC14(void *, s32);
extern void func_80025964(Source *);

void func_80025E3C(Source *src, Owner **dst)
{
    s32 i;

    dst[0]->unk0 = D_80078C10;
    dst[0]->unk4->unkA = 0;

    dst[1]->unk0 = D_800789B8;
    dst[1]->unk4->unk8 = -20;

    dst[2]->unk0 = src->unk74 + 12;
    dst[2]->unk4->unk8 = -20;
    func_80025888(dst, 0);

    dst[3]->unk0 = src->unk74;
    dst[3]->unk4->unkA = -64;
    func_80025C6C(src->unk74 + 24);

    dst[4]->unk0 = src->unk74 + 24;
    dst[4]->unk4->unk8 = -20;
    dst[4]->unk4->unkA = 8;

    dst[5]->unk0 = func_8004DC14(D_80029474, 0);
    dst[5]->unk4->unk8 = 124;
    dst[5]->unk4->unkA = 72;

    for (i = 6; i < 11; i++) {
        dst[i]->unk0 = D_8007795C;
        dst[i]->unk4->unk8 = -12;
        dst[i]->unk4->unkA = (i * 16) - 137;
    }

    func_80025964(src);
    dst[12]->unk4->unk8 = -12;
    dst[12]->unk4->unkA = 23;
}
