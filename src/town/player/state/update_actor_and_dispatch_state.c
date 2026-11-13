#include "common.h"
#include "town/player/scene_action_setup.h"
#include "shared/entity.h"
#include "town/player/state.h"

#include "town/player/store_the_valid_shared_angle_in_offset_hex_10_api.h"                         /* extern */
#include "town/player/clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2_api.h"                      /* extern */
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"                      /* extern */
#include "town/player.h"
#include "town/player/position_handlers.h"
struct EntityRec; void update_position_upper_bound(ObjectPosition *);                      /* extern */
extern u8 town_blocked_directions;


/* Update the actor record and dispatch follow-up processing when its state is nonnegative. */
void update_actor_and_dispatch_state(void *actor, ObjectPosition *record, s32 context) {
    update_position_upper_bound(record);
    resolve_collision_axis_order(record);
    store_input_angle(actor);
    accelerate_toward_input_keep_speed(record);
    if (town_blocked_directions != 0) {
        record->velocity_z = 0;
        copy_z_to_collision_motion((record));
    } else {
        add_vertical_gravity(record);
    }
    if (record->velocity_z >= 0) {
        initialize_threshold_interaction_action(actor, record, context);
    }
}
