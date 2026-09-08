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

/* Initialize the owner with default patch and auxiliary data. */
void func_800267D8(void *unused, Owner *owner, S_8002E5D8 *patch_data,
                   S_8002E5E8 *aux_data) {
    S_8002E5D8 *patch_defaults = &D_8002E5D8;
    S_8002E5E8 *aux_defaults = &D_8002E5E8;
    s32 *aux_first_word;

    patch_data->unk0 = patch_defaults->unk0;
    aux_first_word = &aux_defaults->unk0;
    patch_data->unk4 = patch_defaults->unk4;
    patch_data->unk8 = patch_defaults->unk8;
    patch_data->unkC = patch_defaults->unkC;

    aux_data->unk0 = *aux_first_word;
    aux_data->unk4 = aux_defaults->unk4;
    aux_data->unk8 = aux_defaults->unk8;

    owner->unk4 = (PatchRecord *)patch_data;
    owner->unk8 = aux_data;
    owner->unk0 = 0;

    owner->unk4->unk8 = -96;
    owner->unk4->unkA = -112;
    owner->unk4->unkC = 0x200;
    owner->unk4->unk6 = 0;
    owner->unk4->unkF = 4;
}
