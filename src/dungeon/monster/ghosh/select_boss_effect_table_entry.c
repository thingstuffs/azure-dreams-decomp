#include "common.h"
#include "dungeon/monster/ghosh.h"

typedef s32 M2C_UNK;


extern u8 *D_80174BEC[];

/* Select a table entry, reset its counter, and set the object flag. */
void select_boss_effect_table_entry(s32 table_index) {
    ghosh_command_ticks = 0;
    ghosh_command_stream = D_80174BEC[table_index];
    *(s16 *)((s8 *)ghosh_boss_node + 0xD2) = 1;
}
