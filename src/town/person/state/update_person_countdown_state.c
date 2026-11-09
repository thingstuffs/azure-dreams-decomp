#include "town/person/state_callbacks_api.h"
#include "common.h"
#include "town/person/motion.h"
#include "town.h"

typedef struct town_person_countdown_state {
    u8 pad_00[0x50];
    void *state;
    u8 pad_54[0x18];
    u16 timer;
    u8 pad_6E[0x22];
    s16 value;
} State;




/* Updates the state from the value and countdown, resetting an expired timer to ten. */
void update_person_countdown_state(State *record) {
    u16 timer;

    if (record->value < 100) {
        record->state = move_person_toward_sample;
    }
    timer = record->timer - 1;
    record->timer = timer;
    if ((s16) timer < 0) {
        record->state = update_timed_state_transition;
        record->timer = 10;
    }
}
