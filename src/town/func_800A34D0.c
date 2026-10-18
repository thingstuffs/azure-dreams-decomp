#include "modules/town_door.h"

void select_tower_entry_handler_by_item_count(S_800A0C30_0 *script_state, void *unused_context, S_800A0C30_1 *event_params) {
    if (check_door_input_and_angle(script_state, unused_context) != 0) {
        if (count_consecutive_nonzero_entries_up_twenty() < 6) {
            script_state->unk_90 = 6;
            script_state->unk_50 = &update_door_completion_state;
            initialize_entity_handlers_and_position(script_state->unk_72, event_params->unk_02, event_params->unk_06);
            return;
        }
        script_state->unk_50 = &set_door_handler_if_ready;
        set_player_block_value(script_state->unk_72);
    }
}
