#include "common.h"
#include "shared/town_object.h"


#include "town/person/object_setup.h"
#include "town/person.h"
#include "town/person/object.h"


/* Advances two values toward their targets and finalizes when the countdown expires. */
void advance_mother_event_values(TownObjectRecord *state, MotherEventValues *values, SpriteFrameState *setup_context) {
    u16 steps_left;

    steps_left = state->timer - 1;
    state->timer = steps_left;
    if ((s16) steps_left <= 0) {
        apply_object_setup_and_update(state, values, setup_context);
        values->unk_02 = (u16) ((u16)state->unk_84);
        values->unk_06 = state->unk_86;
        return;
    }
    values->unk_02 = (u16) (values->unk_02 + ((s32) ((s16) ((u16)state->unk_84)
        - (s16) values->unk_02) / (s16) steps_left));
    values->unk_06 = (s16) ((u16) values->unk_06 + ((s32) (state->unk_86
        - values->unk_06) / (s16) state->timer));
}
