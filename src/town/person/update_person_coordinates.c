#include "common.h"
#include "town/person/lookup_motion.h"
#include "town/person.h"
#include "town/person/motion.h"
#include "town/person/state_callbacks_api.h"

/* Updates coordinates and selects the state handler based on the threshold and timer. */
void update_person_coordinates(TownObjectRecord *state, ObjectPosition *coords) {
    u16 timer;

    if (state->unk_90 < 100) {
        state->state_callback.as_pm = move_person_toward_sample;
    }
    coords->x.unsigned_parts.integer = ((u32)coords->velocity_x >> 16);
    coords->y.unsigned_parts.integer = ((u32)coords->velocity_y >> 16);
    coords->z.w.i = ((u32)coords->velocity_z >> 16) + advance_person_sine_offset(state);
    timer = state->timer - 1;
    state->timer = timer;
    if ((s16)timer < 0) {
        state->state_callback.as_pm = advance_person_state_value;
        state->timer = 10;
    }
}
