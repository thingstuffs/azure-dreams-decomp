#include "common.h"
#include "dungeon/monster/beldo_large_data.h"
#include "m2c_compat.h"
#include "dungeon/monster/beldo_large.h"
#include "shared/entity.h"


/* Clear two state fields and advance the byte counter. */
void advance_multi_form_actor_action(void) {
    ActorRecord *state;

    state = NODE_BODY(beldo_actor_nodes);
    state->action_phase = 0;
    state->action_timer = 0;
    state->action_id = (u8) (state->action_id + 1);
}
