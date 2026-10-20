#include "common.h"
#include "shared/entity.h"

void initialize_threshold_interaction_action();        /* extern */
void store_the_valid_shared_angle_in_offset_hex_10();                         /* extern */
void handle_adjust_vector_toward_selected_angle_limit_magnitude();                      /* extern */
void add_hex_20000_s_signed_offset_hex_14();                      /* extern */
void clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2();                      /* extern */
void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile();                      /* extern */
void update_the_computed_upper_bound_global_state_permits();                      /* extern */
extern u8 D_800CFCEE;


/* Update the actor record and dispatch follow-up processing when its state is nonnegative. */
void update_actor_and_dispatch_state(s32 actor, EntityRec *record, s32 context) {
    update_the_computed_upper_bound_global_state_permits(record);
    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(record);
    store_the_valid_shared_angle_in_offset_hex_10(actor);
    handle_adjust_vector_toward_selected_angle_limit_magnitude(record);
    if (D_800CFCEE != 0) {
        record->flags14 = 0;
        clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2(record);
    } else {
        add_hex_20000_s_signed_offset_hex_14(record);
    }
    if (record->flags14 >= 0) {
        initialize_threshold_interaction_action(actor, record, context);
    }
}
