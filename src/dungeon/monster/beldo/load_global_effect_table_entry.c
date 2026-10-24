#include "common.h"

extern s32 beldo_effect_scripts[];
extern s32 *beldo_active_entity;
extern s32 beldo_effect_stream;
extern s16 beldo_command_ticks;

/* Loads the selected table entry and marks the object state with its index. */
void load_global_effect_table_entry(s32 entry_index) {
    s8 *state_data;

    beldo_command_ticks = 0;
    state_data = (s8 *)beldo_active_entity + 0x20;
    beldo_effect_stream = beldo_effect_scripts[entry_index];
    state_data[0xBA] = 1;
    *(s16 *)(state_data + 0xB8) = entry_index;
}
