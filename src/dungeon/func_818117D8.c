#include "modules/dungeon_ovl_1831370.h"

void dungeonInitializeOwnerDefaults(void *unused, ovl_1831370_818117D8_Owner *owner, ovl_1831370_818117D8_S_8002E5D8 *patch_data,
                   ovl_1831370_818117D8_S_8002E5E8 *aux_data) {
    ovl_1831370_818117D8_S_8002E5D8 *patch_defaults = &D_8002E5D8;
    ovl_1831370_818117D8_S_8002E5E8 *aux_defaults = &D_8002E5E8;
    s32 *aux_first_word;

    patch_data->unk0 = patch_defaults->unk0;
    aux_first_word = &aux_defaults->unk0;
    patch_data->unk4 = patch_defaults->unk4;
    patch_data->unk8 = patch_defaults->unk8;
    patch_data->unkC = patch_defaults->unkC;

    aux_data->unk0 = *aux_first_word;
    aux_data->unk4 = aux_defaults->unk4;
    aux_data->unk8 = aux_defaults->unk8;

    owner->unk4 = (ovl_1831370_818117D8_PatchRecord *)patch_data;
    owner->unk8 = aux_data;
    owner->unk0 = 0;

    owner->unk4->unk8 = -96;
    owner->unk4->unkA = -112;
    owner->unk4->unkC = 0x200;
    owner->unk4->unk6 = 0;
    owner->unk4->unkF = 4;
}
