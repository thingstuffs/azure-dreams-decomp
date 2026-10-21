#include "common.h"

extern s32 D_801749BC[];
extern s32 *ghosh_actor_node;
extern s32 D_80174CCC;
extern s16 D_80174CD0;

/* Select a table entry, reset its counter, and mark the object state active. */
void select_encounter_action_script(s32 table_index) {
    s8 *state;

    D_80174CD0 = 0;
    state = (s8 *)ghosh_actor_node + 0x20;
    D_80174CCC = D_801749BC[table_index];
    state[0xB2] = 1;
    *(s16 *)(state + 0xAC) = table_index;
}
