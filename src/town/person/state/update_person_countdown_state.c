#include "common.h"

typedef struct {
    u8 pad_00[0x50];
    void *state;
    u8 pad_54[0x18];
    u16 timer;
    u8 pad_6E[0x22];
    s16 value;
} State;

extern u8 D_800AB55C[];
extern u8 person_approach_state_address[];

/* Updates the state from the value and countdown, resetting an expired timer to ten. */
void update_person_countdown_state(State *record) {
    u16 timer;

    if (record->value < 100) {
        record->state = person_approach_state_address;
    }
    timer = record->timer - 1;
    record->timer = timer;
    if ((s16) timer < 0) {
        record->state = D_800AB55C;
        record->timer = 10;
    }
}
