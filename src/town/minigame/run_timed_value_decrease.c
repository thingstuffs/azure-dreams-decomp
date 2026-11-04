#include "common.h"
#include "shared/entity.h"
#include "town/person/effects.h"
#include "sdk/libc.h"
#include "town/minigame.h"
#include "town/minigame/keima.h"


/* Runs a 24-tick value decrease with random callbacks, then waits to reset. */
void run_timed_value_decrease(TimedValueDecreaseObject *sequence, ObjectPosition *target)
{
    s16 state;
    s32 ticks_left;
    u16 next_state;
    KeimaState *owner;

    state = sequence->state.s;
    owner = sequence->owner;

    switch (state) {
    case 0:
    {

        if (owner->stage.s != 3) {
            break;
        }
        state = 0x18;
        next_state = sequence->state.u;
        sequence->timer = state;
        sequence->state.u = next_state + 1;
        break;
    }

    case 1:
        target->y.v += 0xFFF00000;
        if (!(rand() & 7)) {
            spawn_person_radial_effects(target);
        }
        ticks_left = sequence->timer - 1;
        sequence->timer = ticks_left;
        if ((ticks_left << 16) > 0) {
            break;
        }
        next_state = sequence->state.u;

        sequence->state.u = next_state + 1;
        break;

    case 2:
        if (owner->stage.s < 3) {
            sequence->state.s = 0;
            target->y.v += 0x01400000;
        }
        break;
    }
}
