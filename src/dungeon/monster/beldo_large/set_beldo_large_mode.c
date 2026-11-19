#include "common.h"
#include "dungeon/monster/beldo_large_data.h"
#include "dungeon/monster/beldo_large.h"

/* Stores the Beldo script data mode and clears its next pointer and timer. */
void set_beldo_large_mode(s32 value) {
    ActorRecord *state = NODE_BODY(beldo_script_node);
    state->action_id = value; state->action_phase = 0; state->action_timer = 0;
}
