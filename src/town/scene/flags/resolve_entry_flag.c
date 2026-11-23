#include "common.h"

#include "town/scene/entry_requests.h"
#include "town/player/script_flags.h"
#include "town/scene/flags.h"
#include "town/scene.h"

/* Resolve a table entry to its referenced flag and query that flag. */
s32 resolve_entry_flag(void *entry_table, TownObjectSet *context, s32 entry_key) {
    ScenePositionEntry *entries = entry_table;
    s32 entry_index;
    s32 flag_index;

    entry_index = find_eight_byte_entry_or_assert(entries, entry_key);
    flag_index = entries[entry_index].selector;
    return get_script_flag_mask(context->flag_dependencies[flag_index].clear_flag);
}
