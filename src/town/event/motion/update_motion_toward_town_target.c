#include "common.h"
#include "town/scene/collision.h"
#include "shared/entity_objects.h"
#include "town/player/position.h"
#include "town/scene/motion.h"

extern void call_the_same_context_both_processing_routines(void *value, void *context);
extern void initialize_object_and_maybe_play_sound(void *context, s32 object, void *state, s32 extra);

/* Update target-relative motion and advance when the countdown expires. */
void update_motion_toward_town_target(void *state, s32 context, void *motion, s32 next_arg) {
    u16 ticks_left;

    *(s32 *)((u8 *)motion + 0xC) = (view_reference_entity.x.v - *(s32 *)motion) / 2;
    *(s32 *)((u8 *)motion + 0x10) = (view_reference_entity.y.v - *(s32 *)((u8 *)motion + 4)) / 2;
    add_motion_deltas_to_position(motion);
    call_the_same_context_both_processing_routines(context, motion);
    handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(context, motion);
    ticks_left = *(u16 *)((u8 *)state + 0x6C) - 1;
    *(u16 *)((u8 *)state + 0x6C) = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        initialize_object_and_maybe_play_sound(state, context, motion, next_arg);
    }
}
