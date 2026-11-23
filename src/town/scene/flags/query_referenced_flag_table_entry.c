#include "common.h"
#include "town/scene/position_entries.h"
#include "town/scene/flags.h"
#include "town/player/state.h"
#include "town/scene.h"

/* Copy, in this TOWN script module, of the module-0 helper resolve_entry_flag (src/town/func_8032F544.c);
 * this build reads the flag number from offset 0x4 of the flag record. */

/* Resolve a table entry to its referenced flag and return that flag's query result. */
s32 query_referenced_flag_for_table_entry(ScenePositionEntry *entry_table, TownObjectSet *context, s32 entry_key) {
    s32 entry_index;

    entry_index = find_eight_byte_entry_or_assert(entry_table, entry_key);
    return get_script_flag_mask(context->flag_dependencies[entry_table[entry_index].selector].target_flag);
}
