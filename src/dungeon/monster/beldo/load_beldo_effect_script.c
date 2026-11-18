#include "common.h"
#include "shared/object_node.h"
#include "dungeon/monster/beldo.h"
#include "dungeon/monster/beldo/command_ticks_data.h"

/* Loads the selected table entry and marks the object state with its index. */
void load_beldo_effect_script(s32 entry_index) {
    BeldoEffectScriptState *state_data;

    beldo_command_ticks = 0;
    state_data = NODE_BODY(beldo_active_entity);
    beldo_effect_stream = beldo_effect_scripts[entry_index];
    state_data->script_active = 1;
    state_data->script_index = entry_index;
}
