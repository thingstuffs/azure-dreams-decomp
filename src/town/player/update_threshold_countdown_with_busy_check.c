#include "town/player/position_handlers.h"
#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "town/player/coordinates.h"
#include "town.h"
#include "town/player.h"
#include "town/player/position.h"
#include "town/shop.h"

extern void install_actor_interaction_handler(void *state, void *object, s32 context);

/* Update the object, handle its value threshold, and advance the countdown. */
void update_threshold_countdown_with_busy_check(void *state, ObjectPosition *object, s32 context) {
    s16 target_value;
    u16 countdown;

    resolve_collision_axis_order(object);
    apply_velocity_friction(object);
    if (is_map_state_in_special_range() == 0) {
        target_value = query_capped_surface_height(object, &position_query_scratch);
        if (target_value - object->z.w.i >= 4) {
            if (town_action_state_flag == 0) {
                initialize_action_object(state, object, context);
                return;
            }
        } else {
            if (town_action_state_flag == 0) {
                set_height_and_slope_velocity(object, target_value, &position_query_scratch);
            }
        }
    }

    countdown = *(u16 *)((u8 *)state + 0xA) - 1;
    *(u16 *)((u8 *)state + 0xA) = countdown;
    if ((s16)countdown < 0) {
        install_actor_interaction_handler(state, object, context);
    }
}
