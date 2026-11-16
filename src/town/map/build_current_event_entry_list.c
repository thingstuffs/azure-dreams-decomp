#include "common.h"
#include "m2c_compat.h"
#include "town/map.h"
#include "town/data.h"
#include "town/map/event_entry_data.h"

extern s32 *D_800718B0[];

/* Build a null-terminated list with one or three entries for the current event. */
void build_current_event_entry_list(void) {
    s32 **entries;
    s32 entry_count;

    entries = D_800718B0;
    entries[0] = town_map_primary_entry;
    entry_count = 1;
    if (town_map_event_kind != 0x17) {
        entry_count = 3;
        entries[1] = town_map_secondary_entry;
        entries[2] = town_map_tertiary_entry;
    }
    entries[entry_count] = NULL;
}
