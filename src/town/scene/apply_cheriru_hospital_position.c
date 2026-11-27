#include "script_symbols.h"
#include "common.h"
#include "town/scene/position_entries.h"
#include "town/scene.h"
#include "town/data.h"
#include "town/player/state.h"

extern ScenePositionEntry hospital_cherrl_trigger_clear_position;
extern ScenePositionEntry hospital_cherrl_trigger_set_position;

/* Selects data using query 0xFBC and forwards it with the supplied values. */
void apply_cherrl_hospital_position(TownObjectSet *primaryValue, s32 unusedValue, s32 secondaryValue) {

    if (get_script_flag_mask(F_chriru_hospital_trg) != 0) {
        apply_entry_position(&hospital_cherrl_trigger_set_position, &scene_request_context, primaryValue, secondaryValue);
    } else {
        apply_entry_position(&hospital_cherrl_trigger_clear_position, &scene_request_context, primaryValue, secondaryValue);
    }
}
