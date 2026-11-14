#include "town/player/position_handlers.h"
#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "town/player/coordinates.h"
#include "town.h"
#include "town/player.h"
#include "town/player/position.h"
#include "shared/sprite_frame_state.h"

/* Update the object, check its target value, and advance the countdown. */
void update_ground_countdown_action(void *state, ObjectPosition *object, SpriteFrameState *context) {
    s16 target_value;
    u16 countdown;

    resolve_collision_axis_order(object);
    apply_velocity_friction(object);
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

    countdown = *(u16 *)((u8 *)state + 0xA) - 1;
    *(u16 *)((u8 *)state + 0xA) = countdown;
    if ((s16)countdown < 0) {
        initialize_timed_scene_action(state, object, context);
    }
}
