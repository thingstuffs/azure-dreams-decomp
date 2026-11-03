#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"
#include "town/scene/response_checks.h"
#include "town/scene/dialogue.h"
#include "town/player/state.h"

/* Selects dialogue, then applies a script-flag response or state fallback when the table check passes. */
s32 select_dialogue_with_799_override(s32 speaker, s32 interaction, s32 dialogue_id) {
    s32 dialogue;

    if (check_table_result_below_minus_47() != 0) {

        return &scene_result_fallback;
    }
    dialogue = apply_entry_position(&D_8001A97C, &scene_response_context, speaker, dialogue_id);
    if (resolve_entry_flag(&D_8001A97C, speaker, dialogue_id) != 0) {
        if (get_script_flag_mask(F_sbs22_pad29) != 0) {

            dialogue = &D_8001CDF2;
        } else {
            dialogue = select_state_result_with_lookup_overrides(speaker, interaction, dialogue_id);
        }
    }
    return dialogue;
}
