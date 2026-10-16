/* Relink of matched dungeon/func_80CE9E78; every changed retail word is a paired relocation. */
#define dungeonResetActorDirectionalAnimation func_8016D678
#define D_80175E9C D_8016FE9C
#define D_80175EA4 D_8016FEA4
#define D_80175EAC D_8016FEAC
#include "modules/dungeon_ovl_7f469800_p03.h"

/* Reset display state and apply the kind-specific directional entry when its table changes. */
void func_8016D678(Rec_func_80172CC0_arg0 *state, s32 unused, Rec_D_80082E80 *display, T_80173678_S_80173678_1 *entity) {
    s32 kind;
    u8 *direction_table;
    u8 *previous_table;

    state->unk_9A.as_s8 = 0x10;
    state->unk_9B.as_s8 = 0;
    kind = entity->unk_48;
    switch (kind) {
    case 0xD:
        direction_table = D_8016FE9C;
        previous_table = display->unk_2C.as_pu8;
        if (previous_table == direction_table) {
            return;
        }
        display->unk_2C.as_pu8 = direction_table;
        func_80047784(display,
                      direction_table[((gameWork.view.viewAngle + entity->unk_2A + 0x100) >> 9) & 7],
                      0);
        return;
    case 0xE:
        direction_table = D_8016FEA4;
        previous_table = display->unk_2C.as_pu8;
        if (previous_table == direction_table) {
            return;
        }
        display->unk_2C.as_pu8 = direction_table;
        func_80047784(display,
                      direction_table[((gameWork.view.viewAngle + entity->unk_2A + 0x100) >> 9) & 7],
                      0);
        return;
    case 0xF:
        direction_table = D_8016FEAC;
        previous_table = display->unk_2C.as_pu8;
        if (previous_table == direction_table) {
            return;
        }
        display->unk_2C.as_pu8 = direction_table;
        func_80047784(display,
                      direction_table[((gameWork.view.viewAngle + entity->unk_2A + 0x100) >> 9) & 7],
                      0);
    }
}
