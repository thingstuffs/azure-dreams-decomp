#include "common.h"
#include "town/scene/collision.h"
#include "shared/entity_objects.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_8009B828_arg0.h"
#include "town/player/position.h"
#include "town/scene/motion.h"

void call_the_same_context_both_processing_routines(s32, s32);             /* extern */
void initialize_target_motion(); /* Unprototyped: retail call passes more arguments than the callee reads */ /* extern */
extern s32 town_target_height_offset;


/* Update motion toward the shared target and advance state when the countdown expires. */
void update_motion_toward_shared_target(Rec_func_8009B828_arg0 *state, s32 context, ObjectPosition *motion, s32 transition_arg) {
    s32 position;
    u16 ticks_left;

    position = motion->z.v;
    motion->velocity_z = (s32) ((s32) ((view_reference_entity.z.v + town_target_height_offset) - position) / 2);
    add_motion_deltas_to_position(motion);
    call_the_same_context_both_processing_routines(context, (s32)(motion));
    handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis((void *)(context), motion);
    ticks_left = state->unk_6C.as_u16 - 1;
    state->unk_6C.as_u16 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        initialize_target_motion(state, context, motion, transition_arg);
    }
}
