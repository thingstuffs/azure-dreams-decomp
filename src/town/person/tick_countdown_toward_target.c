#include "common.h"
#include "shared/town_object.h"
#include "shared/position_views.h"

/* extern */


   /* arg1 in tick_countdown_toward_target */


#include "town/person/object_setup.h"
#include "town/person.h"
#include "town/person/object.h"
/* Decrement the countdown and ease the current values toward their targets. */
void tick_countdown_toward_target(TownObjectRecord *state, SignedPositionView *current, void *context) {
    u16 ticks_left;
    u32 target_delta;

    ticks_left = state->timer - 1;
    state->timer = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        apply_object_setup_and_update(state, current, context);
    }
    current->x = (s16) ((u16) current->x + ((s32) (state->unk_84 - current->x) / 2));
    target_delta = (state->unk_86) - current->y;
    current->z = (s16) ((u16) current->z + ((s32) (0 - current->z) / 2));
    current->y = (s16) ((u16) current->y + ((s32) (target_delta + (target_delta >> 0x1F)) >> 1));
}
