#include "common.h"
#include "dungeon/monster/ghosh.h"

extern u8 *D_801749BC[];

/* Select a table entry, reset its counter, and mark the object state active. */
void select_encounter_action_script(s32 table_index) {
    s8 *state;

    ghosh_script_repeat_count = 0;
    state = (s8 *)(ghosh_actor_node + 1);
    ghosh_script_cursor = D_801749BC[table_index];
    state[0xB2] = 1;
    *(s16 *)(state + 0xAC) = table_index;
}
