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

    resolve_collision_axis_order(entity);
    apply_velocity_friction(entity);
    countdown = ((u16)state->unk_0A) - 1;
    state->unk_0A = countdown;
    if (countdown < 0) {
        clear_entity_record_fields(entity);
        sync_collision_motion_xyz(entity);
        if (town_interaction_pending != 0 && create_item_menu_unless_minigame((s32)(state_arg - 0x20)) != 0) {
            dispatch_selected_entry_if_nonzero((s32 *)(&town_scene_record_handlers), state_arg, transition_arg);
            initialize_shared_scene_data(state_arg, entity, transition_arg);
            return;
        }
        initialize_scene_action_record(state_arg, entity, transition_arg);
    }
}
