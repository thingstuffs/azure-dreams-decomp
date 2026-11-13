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
    store_input_angle(object);
    accelerate_toward_input_angle(motion);
    dispatch_selected_entry_if_nonzero(D_800D0098, object, sprite);
    object->unk_00 = update_actor_input_and_interaction;
    object->unk_0A = (s16) (scale_random_by_limit(2) + 0xC);
}
