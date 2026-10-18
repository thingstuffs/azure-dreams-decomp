#include "common.h"
#include "records/Rec_func_80094268_arg0.h"



void initialize_shared_scene_data();       /* extern */
void initialize_scene_action_record();       /* extern */
void call_the_handler_selects_nonzero_entry();       /* extern */
s32 run_the_action_sequence_context_unless_flag_hex_a_5_set();           /* extern */
void move_both_components_toward_zero_direction_dependent_steps_clamping_zero();       /* extern */
void run_the_three_update_routines_context();       /* extern */
void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile();       /* extern */
void clear_entity_record_fields();       /* extern */
extern u8 D_800D0078[];
extern s32 D_800FE518;


/* Updates the entity and dispatches a state transition when its countdown expires. */
void update_entity_and_dispatch_timed_state(void *state, void *entity, s32 transition_arg) {
    s16 countdown;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(entity);
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero(entity);
    countdown = ((Rec_func_80094268_arg0 *)state)->unk_0A.as_u16 - 1;
    ((Rec_func_80094268_arg0 *)state)->unk_0A.as_u16 = countdown;
    if (countdown < 0) {
        clear_entity_record_fields(entity);
        run_the_three_update_routines_context(entity);
        if (D_800FE518 != 0 && run_the_action_sequence_context_unless_flag_hex_a_5_set(state - 0x20) != 0) {
            call_the_handler_selects_nonzero_entry(&D_800D0078, state, transition_arg);
            initialize_shared_scene_data(state, entity, transition_arg);
            return;
        }
        initialize_scene_action_record(state, entity, transition_arg);
    }
}
