#include "common.h"
#include "dungeon/monster/beldo_large_data.h"
#include "m2c_compat.h"
#include "dungeon/monster/beldo_large.h"



/* Sets the state ID and clears the associated byte and halfword. */
void set_multi_form_actor_action(s8 state_id) {
    ActorRecord *state;

    state = NODE_BODY(beldo_actor_nodes);
    state->action_id = state_id;
    state->action_phase = 0;
    state->action_timer = 0;
}
