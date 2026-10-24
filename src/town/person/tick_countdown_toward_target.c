#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/position_views.h"

/* extern */


   /* arg1 in tick_countdown_toward_target */


#include "town/person/object_setup.h"
/* Decrement the countdown and ease the current values toward their targets. */
void tick_countdown_toward_target(Rec_func_80094268_arg0 *state, SignedPositionView *current, void *context) {
    u16 ticks_left;
    u32 target_delta;

    ticks_left = state->unk_6C.as_u16 - 1;
    state->unk_6C.as_u16 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        apply_object_setup_and_update(state, current, context);
    }
    current->x = (s16) ((u16) current->x + ((s32) (state->unk_84.as_s16 - current->x) / 2));
    target_delta = state->unk_86.as_s16 - current->y;
    current->z = (s16) ((u16) current->z + ((s32) (0 - current->z) / 2));
    current->y = (s16) ((u16) current->y + ((s32) (target_delta + (target_delta >> 0x1F)) >> 1));
}
