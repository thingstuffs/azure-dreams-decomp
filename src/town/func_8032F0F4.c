#include "common.h"

extern s32 townFindEntry8IndexOrAssert(s32 entries, s32 entry_id);
extern void townUpdateDependentEntryIds(s16 checked_id, s16 first_id, s16 second_id);

void townApplyEntryKeyedValues(s32 entryTable, void *resource, s32 entryKey) {
    s32 selector;
    s32 table;
    s16 *valueRecord;

    selector = *(s16 *)(entryTable + (townFindEntry8IndexOrAssert(entryTable, entryKey) * 8) + 2);
    table = *(s32 *)((u8 *)resource + 0x14);
    valueRecord = (s16 *)(selector * 8 + table);
    townUpdateDependentEntryIds(valueRecord[0], valueRecord[1], valueRecord[2]);
}
