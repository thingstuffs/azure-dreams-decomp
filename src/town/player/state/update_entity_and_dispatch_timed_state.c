#include "common.h"
#include "town/player/state_update_g00548.h"
#include "town/player/initialize_shared_scene_data.h"
#include "shared/town_object.h"
#include "town/player/action_initializers.h"
#include "town/player/state.h"
#include "town/player/object.h"
#include "town/player.h"



#include "town/player/call_the_handler_selects_nonzero_entry_api.h"       /* extern */
#include "town/player/move_both_components_toward_zero_direction_dependent_steps_clamping_zero_api.h"       /* extern */
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"       /* extern */
#include "town/player/object/entity_record_fields.h"       /* extern */
extern s32 town_interaction_pending;


/* Updates the entity and dispatches a state transition when its countdown expires. */
void update_entity_and_dispatch_timed_state(void *state_arg, void *entity, void *transition_arg) {
    TownObjectRecord *state = state_arg;
    s16 countdown;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(entity);
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero(entity);
    countdown = ((u16)state->unk_0A) - 1;
    state->unk_0A = countdown;
    if (countdown < 0) {
        clear_entity_record_fields(entity);
        run_the_three_update_routines_context(entity);
        if (town_interaction_pending != 0 && run_the_action_sequence_context_unless_flag_hex_a_5_set((s32)(state_arg - 0x20)) != 0) {
            call_the_handler_selects_nonzero_entry((s32 *)(&town_scene_record_handlers), state_arg, transition_arg);
            initialize_shared_scene_data(state_arg, entity, transition_arg);
            return;
        }
        initialize_scene_action_record(state_arg, entity, transition_arg);
    }
}
