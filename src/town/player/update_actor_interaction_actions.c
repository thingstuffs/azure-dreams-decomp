#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "shared/game_work.h"
#include "shared/position_views.h"
#include "town/player/coordinates.h"
#include "town.h"
#include "town/player.h"
#include "town/player/motion.h"
#include "town/player/position.h"
#include "town/player/state.h"
#include "town/shop.h"

   /* target in update_actor_interaction_actions */

   /* &D_800CFCEF in update_actor_interaction_actions */

   /* self in update_actor_interaction_actions */


/* Updates the target and dispatches actions based on its value, a countdown, and state flags. */
void update_actor_interaction_actions(void *self_arg, ObjectPosition *target_arg, SpriteFrameState *sprite) {
    UnsignedCountdownView *self;
    SpriteFrameState *context;
    s16 target_value;
    u16 countdown;
    u16 busy_countdown;
    GameWork *state;

    context = sprite;
    state = &g_game_work;

    resolve_collision_axis_order(target_arg);
    self = self_arg;

    apply_velocity_friction(target_arg);
    if (is_map_state_in_special_range() == 0) {
        target_value = query_capped_surface_height(target_arg, &position_query_scratch);
        if ((target_value - target_arg->z.w.i) >= 4) {
            if (town_action_state_flag == 0) {
                initialize_action_object(self, target_arg, context);
                return;
            }
        } else if (town_action_state_flag == 0) {
            set_height_and_slope_velocity(target_arg, target_value, &position_query_scratch);
        }
        countdown = self->unk_0A - 1;
        self->unk_0A = countdown;
        if ((s16) countdown >= 0) {
            if (state->buttons & 0xF000) {
                initialize_motion_action(self, target_arg, context);
                return;
            }
            if ((state->pressed_buttons) & 0x10) {
                initialize_actor_action_state(self, target_arg, (s32)context);
                return;
            }
            return;
        }
    } else {
        busy_countdown = self->unk_0A - 1;
        self->unk_0A = busy_countdown;
        if ((s16) busy_countdown >= 0) {
            return;
        }
    }
    initialize_scene_action_record(self, target_arg, context);
}
