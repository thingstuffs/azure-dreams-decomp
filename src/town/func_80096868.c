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
void call_the_valid_shared_angle_fixed_hex_120000_context_callee_80094_f_58(ObjectPosition *context);


void init_periodic_effect_action(TownObjectRecord *object, ObjectPosition *motion, SpriteFrameState *sprite) {
    object->unk_3E.as_s16 = 6;
    store_the_valid_shared_angle_in_offset_hex_10(object);
    call_the_valid_shared_angle_fixed_hex_120000_context_callee_80094_f_58(motion);
    call_the_handler_selects_nonzero_entry(&player_event_handler_entries, object, sprite);
    object->unk_00.as_pm = reset_action_handler_on_flag;
    object->unk_0A.as_s16 = (s16) (scale_random_to_unsigned_halfword_limit(2) + 0xC);
}
