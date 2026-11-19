#include "shared/sprite_frame_state.h"
#include "common.h"
#include "town/event/object.h"
#include "town/shop/item_lookup.h"
#include "town/shop/state.h"

// Clear the subject flag and run the fallback actor handler if the check fails.
void clear_subject_flag_and_run_fallback(TownObjectRecord *actor, void *subject, ObjectPosition *motion, SpriteFrameState *context) {
    s32 scratch[6];

    *((s8 *)subject + 0x15) = 0;
    if (remove_object_if_item_found(actor, subject, motion, context, scratch) == 0) {
        select_object_value_by_height_band(actor, subject, motion, context);
    }
}
