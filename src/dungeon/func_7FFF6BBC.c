#include "modules/dungeon_ovl_16b08_local.h"

void initialize_threshold_interaction_action(Rec_func_8009431C_arg0 *record) {
    record->unk_00.as_pm = (void *)update_threshold_and_interaction;
    record->unk_0A = 0;
}
