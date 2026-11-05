#include "common.h"
#include "shared/town_handler_entries.h"
#include "shared/town_object.h"
#include "town/player.h"
#include "town/player/object.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"  /* extern */
#include "engine/window.h"
#include "town/player/input.h"



/* Initialize the object state, motion, behavior data, and counter. */
void initialize_randomized_object_action(TownObjectRecord *object, ObjectPosition *motion, SpriteFrameState *sprite) {
    object->unk_3E = 6;
    store_the_valid_shared_angle_in_offset_hex_10(object);
    call_the_valid_shared_angle_fixed_hex_120000_context_callee_80094_f_58(motion);
    call_the_handler_selects_nonzero_entry(D_800D0098, object, sprite);
    object->unk_00 = update_actor_input_and_interaction;
    object->unk_0A = (s16) (scale_random_to_unsigned_halfword_limit(2) + 0xC);
}
