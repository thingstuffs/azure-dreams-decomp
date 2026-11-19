#include "common.h"
#include "dungeon/monster/beldo_large_data.h"
#include "dungeon/monster/beldo_large.h"

/* Clears the Beldo script data timer and advances its mode by one. */
void advance_beldo_large_mode(s32 value) {
    ActorRecord *state = NODE_BODY(beldo_script_node);
    state->action_timer = 0; state->action_id++;
}
