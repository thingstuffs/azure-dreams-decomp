#include "common.h"
#include "m2c_compat.h"
#include "dungeon/monster/beldo_large.h"
#include "shared/entity.h"

extern void *beldo_actor_nodes[3];

/* Clear two state fields and advance the byte counter. */
void advance_multi_form_actor_action(void) {
    ActorRecord *state;

    state = beldo_actor_nodes[0] + 0x20;
    state->action_phase = 0;
    state->action_timer = 0;
    state->action_id = (u8) (state->action_id + 1);
}
