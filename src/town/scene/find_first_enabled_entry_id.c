#include "common.h"
#include "town/scene/indexed_values_data.h"
#include "town/scene.h"
#include "town/player/state.h"

extern u8 D_80017BC0[];

/* Return the first listed entry ID whose value passes the check, or zero. */
s32 find_first_enabled_entry_id(void) {
    s32 list_index = 0;

    if (D_80017BC0[list_index] != 0) {
        TownIndexedValueRecord *entries = town_selection_records;
        do {
            if (get_script_flag_mask(entries[D_80017BC0[list_index]].flag) != 0) {
                break;
            }
            list_index++;
        } while (D_80017BC0[list_index] != 0);
    }
    return D_80017BC0[list_index];
}
