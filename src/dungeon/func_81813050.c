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

/* Initialize the header and its two records from templates with fixed field overrides. */
void func_80028050(void *unused, Header *header, Template0 *record_a, Record1 *record_b) {
    Template0 *defaults_a = &D_8002E5D8;
    Template1 *defaults_b = &D_8002E5E8;
    s32 *first_word;

    record_a->unk0 = defaults_a->unk0;
    first_word = &defaults_b->unk0;
    record_a->unk4 = defaults_a->unk4;
    record_a->unk8 = defaults_a->unk8;
    record_a->unkC = defaults_a->unkC;

    ((Template1 *)record_b)->unk0 = *first_word;
    ((Template1 *)record_b)->unk4 = defaults_b->unk4;
    ((Template1 *)record_b)->unk8 = defaults_b->unk8;

    header->unk4 = (Record0 *)record_a;
    header->unk8 = record_b;
    header->unk0 = 0;

    header->unk4->unk8 = -0x58;
    header->unk4->unkA = -0x40;
    header->unk4->unkC = 0x200;
    header->unk8->unk2 = 0x400;
    header->unk8->unk6 = -0x50;
    header->unk4->unkF = 4;
}
