#include "common.h"
#include "shared/entity_objects.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_8009B828_arg0.h"

void call_the_same_context_both_processing_routines(s32, s32);             /* extern */
void handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(void *, void *);             /* extern */
void add_motion_deltas_to_position();                 /* extern */
void initialize_target_motion(); /* extern */
extern s32 D_800D0428;


/* Update motion toward the shared target and advance state when the countdown expires. */
void update_motion_toward_shared_target(Rec_func_8009B828_arg0 *state, s32 context, EntityRec *motion, s32 transition_arg) {
    s32 position;
    u16 ticks_left;

    position = motion->z.v;
    motion->flags14 = (s32) ((s32) ((D_80083780.z.v + D_800D0428) - position) / 2);
    add_motion_deltas_to_position(motion, position);
    call_the_same_context_both_processing_routines(context, (s32)(motion));
    handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis((void *)(context), motion);
    ticks_left = state->unk_6C.as_u16 - 1;
    state->unk_6C.as_u16 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        initialize_target_motion(state, context, motion, transition_arg);
    }
}
