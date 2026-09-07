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

/* Initialize the owner and its patch and state records from defaults. */
void func_80025D9C(void *unused, Owner *owner, S_8002E5D8 *patch,
                   S_8002E5E8 *state) {
    S_8002E5D8 *patch_defaults = &D_8002E5D8;
    S_8002E5E8 *state_defaults = &D_8002E5E8;
    s32 *state_first_word;

    patch->unk0 = patch_defaults->unk0;
    state_first_word = &state_defaults->unk0;
    patch->unk4 = patch_defaults->unk4;
    patch->unk8 = patch_defaults->unk8;
    patch->unkC = patch_defaults->unkC;

    state->unk0 = *state_first_word;
    state->unk4 = state_defaults->unk4;
    state->unk8 = state_defaults->unk8;

    owner->unk4 = (PatchRecord *)patch;
    owner->unk8 = state;
    owner->unk0 = 0;

    owner->unk4->unk8 = 0x2C;
    owner->unk4->unkA = -8;
    owner->unk4->unkC = 0x200;
    owner->unk4->unk6 = 0;
    owner->unk4->unkF = 4;
}
