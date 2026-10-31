#include "common.h"
#include "m2c_compat.h"
#include "dungeon/monster/beldo_large.h"

extern void *beldo_actor_nodes[3];


/* Clears three state fields in the current object. */
void reset_multi_form_actor_action(void) {
    ActorRecord *state;

    state = beldo_actor_nodes[0] + 0x20;
    state->action_id.s = 0;
    state->action_phase.s = 0;
    state->action_timer.s = 0;
}
