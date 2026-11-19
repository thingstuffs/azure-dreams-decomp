#include "common.h"
#include "dungeon/monster/beldo_large_data.h"
#include "dungeon/monster/beldo_large.h"

/* Clears the mode and timer in the Beldo script node data. */
void reset_beldo_large_state(s32 value) {
    ActorRecord *state = NODE_BODY(beldo_script_node);
    state->action_id = 0; state->action_timer = 0;
}
