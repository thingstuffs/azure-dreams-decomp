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

/* Initialize and attach two instances from templates, then apply their default values. */
void func_800B3688(Owner *owner, Template16 *instance16, Instance12 *instance12) {
    Template16 *template16 = &D_8002E5D8;
    Template12 *template12 = &D_8002E5E8;
    s32 *header_word;

    instance16->unk0 = template16->unk0;
    header_word = &template12->unk0;
    instance16->unk4 = template16->unk4;
    instance16->unk8 = template16->unk8;
    instance16->unkC = template16->unkC;

    ((Template12 *)instance12)->unk0 = *header_word;
    ((Template12 *)instance12)->unk4 = template12->unk4;
    ((Template12 *)instance12)->unk8 = template12->unk8;

    owner->unk4 = (Instance16 *)instance16;
    owner->unk8 = instance12;
    owner->unk0 = 0;

    owner->unk4->unk8 = -60;
    owner->unk4->unkA = -92;
    owner->unk4->unkC = 0x200;
    owner->unk4->unk6 = 0;
    owner->unk8->unk8 = 0x30;
    owner->unk4->unkF = 4;
}
