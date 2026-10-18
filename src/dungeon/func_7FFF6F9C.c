#include "modules/dungeon_ovl_16b08_local.h"

void initialize_actor_interaction_state_19(Rec_func_80094268_arg0 *record) {
    record->unk_00.as_pm = (void *)update_actor_interaction_actions;
    record->unk_0A.as_s16 = 0x13;
}
