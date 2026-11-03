#include "common.h"
#include "shared/town_object.h"
#include "sdk/libgte.h"
#include "town/person.h"
#include "town/person/object.h"


/* Advance the scale animation countdown and restore normal scale when it ends. */
void animate_scale_and_restore(TownObjectRecord *state, void *context, SpriteFrameState *scale) {
    s16 frames_left;
    s32 shrink_value;
    s32 grow_value;
    s32 shrink_amount;

    frames_left = (u16) state->timer.as_s16 - 1;
    state->timer.as_s16 = frames_left;
    if (frames_left <= 0) {
        scale->scale_y = 0x1000;
        scale->scale_x = 0x1000;
        apply_object_setup_and_update(state, context, scale);
        return;
    }
    shrink_value = rsin(frames_left * 0x199);
    shrink_amount = (shrink_value / 4);
    scale->scale_x = (s16) (0x1000 - shrink_amount);
    grow_value = rsin(state->timer.as_s16 * 0x199);
    scale->scale_y = (s16) ((grow_value / 4) + 0x1000);
}
