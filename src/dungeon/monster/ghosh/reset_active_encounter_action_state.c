#include "common.h"
#include "dungeon/monster/ghosh.h"
#include "m2c_compat.h"



/* Clears the two action fields at offsets 0x9B and 0x96 in the Ghosh actor data. */
void reset_active_encounter_action_state(void) {
    ActorRecord *state;
    void *body;

    body = ghosh_actor_node + 1;
    state = body;
    state->action_phase.s = 0;
    state->action_timer.s = 0;
}
