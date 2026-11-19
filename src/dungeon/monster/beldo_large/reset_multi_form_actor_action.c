#include "common.h"
#include "dungeon/monster/beldo_large_data.h"
#include "m2c_compat.h"
#include "dungeon/monster/beldo_large.h"



/* Clears three state fields in the current object. */
void reset_multi_form_actor_action(void) {
    ActorRecord *state;

    state = NODE_BODY(beldo_actor_nodes);
    state->action_id = 0;
    state->action_phase = 0;
    state->action_timer = 0;
}
