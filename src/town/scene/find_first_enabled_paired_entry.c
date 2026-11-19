#include "common.h"
#include "town/scene/indexed_values_data.h"
#include "town/scene.h"
#include "town/player/state.h"

/* Process the first entry whose paired checks pass and fail, returning its index or zero. */
s32 find_first_enabled_paired_entry(void) {
    s32 entry_index;
    TownIndexedValueRecord *entry;
    TownIndexedValueRecord *table_base;

    table_base = town_selection_records;
    for (entry_index = 1; entry_index < 8; entry_index++) {
        entry = &table_base[entry_index];
        if ((get_script_flag_mask(entry->flag) != 0) && (get_script_flag_mask(entry->selected_flag)
            == 0)) {
            set_script_flag_bit(entry->selected_flag);
            return entry_index;
        }
    }
    return 0;
}
