#include "slus/map_state.h"
#include "town/map.h"

typedef struct MapDisplayEntry {
    s32 map_index;
    u8 *text;
    s16 position_offset;
} MapDisplayEntry;

extern MapDisplayEntry D_800D3824[];

/* Creates the display entries for the first row matching the active map. */
void build_display_entries_for_map_state(void)
{
    MapDisplayEntry *entry;
    s32 i;

    for (i = 0; D_800D3824[i].map_index != -1; i++) {
        entry = &D_800D3824[i];
        if (map_runtime_state.map_index == entry->map_index) {
            create_two_text_display_entries(entry->text, entry->position_offset);
            return;
        }
    }
}
