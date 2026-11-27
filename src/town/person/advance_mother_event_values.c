#include "common.h"
#include "shared/town_object.h"


#include "town/person/object_setup.h"
#include "town/person.h"
#include "town/person/object.h"


/* Advances two values toward their targets and finalizes when the countdown expires. */
void advance_mother_event_values(TownObjectRecord *state, ObjectPosition *values, SpriteFrameState *setup_context) {
    u16 steps_left;

    steps_left = state->timer - 1;
    state->timer = steps_left;
    if ((s16) steps_left <= 0) {
        apply_object_setup_and_update(state, values, setup_context);
        values->x.w.i = state->origin_x;
        values->y.w.i = state->origin_y;
        return;
    }
    values->x.w.i = (s16) (values->x.w.i + ((s32) ((s16) ((u16)state->origin_x)
        - values->x.w.i) / (s16) steps_left));
    values->y.w.i = (s16) ((u16) values->y.w.i + ((s32) (state->origin_y
        - values->y.w.i) / (s16) state->timer));
}
