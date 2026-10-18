#include "modules/dungeon_ovl_1830850.h"

void inventory_initialize_owner_patch_and_state(void *unused, ovl_1830850_81810D9C_Owner *owner, ovl_1830850_81810D9C_S_8002E5D8 *patch,
                   ovl_1830850_81810D9C_S_8002E5E8 *state) {
    ovl_1830850_81810D9C_S_8002E5D8 *patch_defaults = &D_8002E5D8;
    ovl_1830850_81810D9C_S_8002E5E8 *state_defaults = &D_8002E5E8;
    s32 *state_first_word;

    patch->unk0 = patch_defaults->unk0;
    state_first_word = &state_defaults->unk0;
    patch->unk4 = patch_defaults->unk4;
    patch->unk8 = patch_defaults->unk8;
    patch->unkC = patch_defaults->unkC;

    state->unk0 = *state_first_word;
    state->unk4 = state_defaults->unk4;
    state->unk8 = state_defaults->unk8;

    owner->unk4 = (ovl_1830850_81810D9C_PatchRecord *)patch;
    owner->unk8 = state;
    owner->unk0 = 0;

    owner->unk4->unk8 = 0x2C;
    owner->unk4->unkA = -8;
    owner->unk4->unkC = 0x200;
    owner->unk4->unk6 = 0;
    owner->unk4->unkF = 4;
}
