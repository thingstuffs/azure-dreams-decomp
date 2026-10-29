#include "common.h"

#include "town/scene/entry_requests.h"
#include "town/scene/flags.h"
#include "town/scene.h"

/*
 * Finds the eight-byte entry by key, uses its selector to index the resource table, and submits
 * the first three halfwords to update_dependent_entry_ids.
 */
void apply_entry_keyed_values(s16 *entryTable, void *resource, s32 entryKey) {
    s32 selector;
    u8 *table;
    s16 *valueRecord;

    selector = entryTable[find_entry_8_index_or_assert(entryTable, entryKey) * 4 + 1];
    table = *(u8 **)((u8 *)resource + 0x14);
    valueRecord = (s16 *)(selector * 8 + (unsigned long)table);
    update_dependent_entry_ids(valueRecord[0], valueRecord[1], valueRecord[2]);
}
