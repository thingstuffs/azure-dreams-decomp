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

/* Initializes owner data pointers and patch offsets from shared and source data. */
void func_80025E3C(Source *source, Owner **owners)
{
    s32 owner_idx;

    owners[0]->unk0 = D_80078C10;
    owners[0]->unk4->unkA = 0;

    owners[1]->unk0 = D_800789B8;
    owners[1]->unk4->unk8 = -20;

    owners[2]->unk0 = source->unk74 + 12;
    owners[2]->unk4->unk8 = -20;
    func_80025888(owners, 0);

    owners[3]->unk0 = source->unk74;
    owners[3]->unk4->unkA = -64;
    func_80025C6C(source->unk74 + 24);

    owners[4]->unk0 = source->unk74 + 24;
    owners[4]->unk4->unk8 = -20;
    owners[4]->unk4->unkA = 8;

    owners[5]->unk0 = func_8004DC14(D_80029474, 0);
    owners[5]->unk4->unk8 = 124;
    owners[5]->unk4->unkA = 72;

    for (owner_idx = 6; owner_idx < 11; owner_idx++) {
        owners[owner_idx]->unk0 = D_8007795C;
        owners[owner_idx]->unk4->unk8 = -12;
        owners[owner_idx]->unk4->unkA = (owner_idx * 16) - 137;
    }

    func_80025964(source);
    owners[12]->unk4->unk8 = -12;
    owners[12]->unk4->unkA = 23;
}
