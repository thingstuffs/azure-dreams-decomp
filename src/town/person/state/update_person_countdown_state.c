#include "town/person/state_callbacks_api.h"
#include "common.h"
#include "town/person/motion.h"
#include "town.h"
#include "town/person/state.h"

/* Updates the state from the value and countdown, resetting an expired timer to ten. */
void update_person_countdown_state(TownObjectRecord *record) {
    u16 timer;

    if (record->unk_90 < 100) {
        record->state_callback.as_pm = move_person_toward_sample;
    }
    timer = record->timer - 1;
    record->timer = timer;
    if ((s16) timer < 0) {
        record->state_callback.as_pm = update_timed_state_transition;
        record->timer = 10;
    }
}
