#include "common.h"

#include "town/scene/entry_requests.h"
#include "town/scene/flags.h"
#include "town/scene.h"

/*
 * Finds the eight-byte entry by key, uses its selector to index the resource table, and submits
 * the first three halfwords to update_dependent_entry_ids.
 */
void apply_entry_keyed_values(ScenePositionEntry *entryTable, TownObjectSet *resource, s32 entryKey) {
    s32 selector;
    const TownFlagDependency *valueRecord;
    TownFlagDependency *table;

    selector = entryTable[find_eight_byte_entry_or_assert(entryTable, entryKey)].selector;
    table = resource->flag_dependencies;
    /* BYTES: Keep the dependency base lw before the selector sll. */
    valueRecord = (const TownFlagDependency *)(selector * 8 + (unsigned long)table);
    update_dependent_entry_ids(valueRecord->source_flag, valueRecord->clear_flag, valueRecord->target_flag);
}
