#include "common.h"

extern s32 find_entry_8_index_or_assert(s32 entries, s32 entry_id);
extern void update_dependent_entry_ids(s16 checked_id, s16 first_id, s16 second_id);

void apply_entry_keyed_values(s32 entryTable, void *resource, s32 entryKey) {
    s32 selector;
    s32 table;
    s16 *valueRecord;

    selector = *(s16 *)(entryTable + (find_entry_8_index_or_assert(entryTable, entryKey) * 8) + 2);
    table = *(s32 *)((u8 *)resource + 0x14);
    valueRecord = (s16 *)(selector * 8 + table);
    update_dependent_entry_ids(valueRecord[0], valueRecord[1], valueRecord[2]);
}
