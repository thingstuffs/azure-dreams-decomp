#include "common.h"
#include "m2c_compat.h"
#include "shared/sprite_frame_state.h"
#include "town/player.h"
#include "town/player/state.h"

/* extern */

   /* arg2 in run_action_then_fallback_on_flag */

/* Run the fallback handler if the value stays unchanged and either 0x6000 flag is set. */
void run_action_then_fallback_on_flag(s32 *value, s32 context, SpriteFlagsView *record) {
    s32 previous_value;

    previous_value = *value;
    dispatch_actor_interaction_actions(value, context, record);
    if ((previous_value == *value) && (record->flags & 0x6000)) {
        initialize_scene_action_record(value, context, record);
    }
}
