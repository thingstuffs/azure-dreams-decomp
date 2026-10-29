#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "town/player/action_initializers.h"
#include "town/player/state.h"



void initialize_shared_scene_data();       /* extern */
#include "town/player/call_the_handler_selects_nonzero_entry_api.h"       /* extern */
#include "town/player/move_both_components_toward_zero_direction_dependent_steps_clamping_zero_api.h"       /* extern */
void run_the_three_update_routines_context(s32);       /* extern */
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"       /* extern */
#include "town/player/object/entity_record_fields.h"       /* extern */
extern u8 town_scene_record_handlers[];
extern s32 town_interaction_pending;


/* Updates the entity and dispatches a state transition when its countdown expires. */
void update_entity_and_dispatch_timed_state(void *state, void *entity, void *transition_arg) {
    s16 countdown;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(entity);
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero(entity);
    countdown = ((Rec_func_80094268_arg0 *)state)->unk_0A.as_u16 - 1;
    ((Rec_func_80094268_arg0 *)state)->unk_0A.as_u16 = countdown;
    if (countdown < 0) {
        clear_entity_record_fields(entity);
        run_the_three_update_routines_context((s32)(entity));
        if (town_interaction_pending != 0 && run_the_action_sequence_context_unless_flag_hex_a_5_set((s32)(state - 0x20)) != 0) {
            call_the_handler_selects_nonzero_entry((s32 *)(&town_scene_record_handlers), state, transition_arg);
            initialize_shared_scene_data(state, entity, transition_arg);
            return;
        }
        initialize_scene_action_record(state, entity, transition_arg);
    }
}
