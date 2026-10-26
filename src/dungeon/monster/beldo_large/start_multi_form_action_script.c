#include "common.h"

extern s32 D_80173D5C;
extern u8 *beldo_actor_nodes[3];
extern s32 encounter_script_cursor;
extern s16 beldo_script_timer;

/* Select a table entry, reset its counter, and record the active index in object state. */
void start_multi_form_action_script(s32 table_index) {
    s8 *state;

    beldo_script_timer = 0;
    state = (s8 *)(beldo_actor_nodes[0] + 0x20);
    encounter_script_cursor = ((s32 *)&D_80173D5C)[table_index];
    state[0xAF] = 1;
    state[0xAB] = table_index;
}
