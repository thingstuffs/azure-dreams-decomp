#include "common.h"
#include "town/scene/indexed_values_data.h"
#include "town/scene.h"
#include "town/player/state.h"

/* Counts entries 1 through 7 whose associated town selection flag is set. */
s32 count_enabled_town_entries(void) {
    s32 matchingEntryCount;
    s32 entryIndex;
    TownIndexedValueRecord *entry;
    TownIndexedValueRecord *entryTable;

    matchingEntryCount = 0;
    entryIndex = 1;
    entryTable = town_selection_records;
    entry = entryTable + 1;
    do {
        if (get_script_flag_mask(entry->flag) != 0) {
            matchingEntryCount += 1;
        }
        entryIndex += 1;
        entry++;
    } while (entryIndex < 8);
    return matchingEntryCount;
}
