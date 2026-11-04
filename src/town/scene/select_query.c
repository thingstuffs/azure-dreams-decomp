#include "script_symbols.h"
#include "common.h"
#include "town/scene/position_entries.h"
#include "town/scene.h"
#include "town/data.h"
#include "town/player/state.h"

extern ScenePositionEntry D_80018E1C;
extern ScenePositionEntry D_80018E34;

/* Selects data using query 0xFBC and forwards it with the supplied values. */
void select_query(void *primaryValue, s32 unusedValue, s32 secondaryValue) {

    if (get_script_flag_mask(F_chriru_hospital_trg) != 0) {
        apply_entry_position(&D_80018E34, &scene_request_context, primaryValue, secondaryValue);
    } else {
        apply_entry_position(&D_80018E1C, &scene_request_context, primaryValue, secondaryValue);
    }
}
