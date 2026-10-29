#include "common.h"
#include "town/player/scene_action_setup.h"
#include "shared/entity.h"
#include "town/player/state.h"

#include "town/player/store_the_valid_shared_angle_in_offset_hex_10_api.h"                         /* extern */
void handle_adjust_vector_toward_selected_angle_limit_magnitude();                      /* extern */
void add_hex_20000_s_signed_offset_hex_14(EntityRec *record);                      /* extern */
#include "town/player/clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2_api.h"                      /* extern */
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"                      /* extern */
#include "town/player.h"
struct EntityRec; void update_the_computed_upper_bound_global_state_permits(struct EntityRec *);                      /* extern */
extern u8 town_blocked_directions;


/* Update the actor record and dispatch follow-up processing when its state is nonnegative. */
void update_actor_and_dispatch_state(void *actor, EntityRec *record, s32 context) {
    update_the_computed_upper_bound_global_state_permits(record);
    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(record);
    store_the_valid_shared_angle_in_offset_hex_10(actor);
    handle_adjust_vector_toward_selected_angle_limit_magnitude(record);
    if (town_blocked_directions != 0) {
        record->flags14 = 0;
        clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2((s32 *)(record));
    } else {
        add_hex_20000_s_signed_offset_hex_14(record);
    }
    if (record->flags14 >= 0) {
        initialize_threshold_interaction_action(actor, record, context);
    }
}
