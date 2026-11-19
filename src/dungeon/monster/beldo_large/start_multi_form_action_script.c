#include "common.h"
#include "dungeon/monster/beldo_large.h"
#include "dungeon/monster/beldo_large_data.h"
#include "dungeon/data.h"

extern u8 *D_80173D5C[];

/* Select a table entry, reset its counter, and record the active index in object state. */
void start_multi_form_action_script(s32 table_index) {
    BeldoScriptControl *state;

    beldo_script_timer = 0;
    state = NODE_BODY(beldo_actor_nodes);
    encounter_script_cursor = D_80173D5C[table_index];
    state->script_active = 1;
    state->script_index = table_index;
}
