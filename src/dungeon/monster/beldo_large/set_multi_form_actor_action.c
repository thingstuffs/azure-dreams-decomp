#include "common.h"
#include "m2c_compat.h"
#include "dungeon/monster/beldo_large.h"

extern void *beldo_actor_nodes[3];


/* Sets the state ID and clears the associated byte and halfword. */
void set_multi_form_actor_action(s8 state_id) {
    ActorRecord *state;

    state = beldo_actor_nodes[0] + 0x20;
    state->action_id.s = state_id;
    state->action_phase.s = 0;
    state->action_timer.s = 0;
}
