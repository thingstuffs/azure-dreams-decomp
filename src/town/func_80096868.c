#include "town/player/action_initializers.h"
/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"
#include "engine/window.h"
#include "town.h"
#include "town/data.h"
#include "shared/sprite_frame_state.h"
#include "town/player.h"

#include "town/player/periodic_action_effect_g00533_api.h"
void accelerate_toward_input_angle(ObjectPosition *context);


void init_periodic_effect_action(TownObjectRecord *object, ObjectPosition *motion, SpriteFrameState *sprite) {
    object->unk_3E = 6;
    store_input_angle(object);
    accelerate_toward_input_angle(motion);
    dispatch_selected_entry_if_nonzero(&player_event_handler_entries, object, sprite);
    object->unk_00 = reset_action_handler_on_flag;
    object->unk_0A = (s16) (scale_random_by_limit(2) + 0xC);
}
