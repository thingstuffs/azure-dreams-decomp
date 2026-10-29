#include "shared/town_event_state.h"
#include "common.h"
#include "town/scene.h"

typedef struct {
    u8 pad0[4];
    s16 value;
    u8 pad6[6];
} Entry;

extern s32 func_8001E670(s32 value);
extern Entry town_selection_records[];
extern u8 town_enabled_entry_order[];

/* Select the next entry whose value passes func_8001E670, wrapping at the terminator. */
s32 advance_to_next_enabled_entry(void) {
    s32 start_index;
    s32 next_index;
    u8 *entry_id;

    start_index = ((s8)town_event_state->entry_index);
    next_index = start_index + 1;
    if (next_index != start_index) {
        Entry *entries = town_selection_records;
        u8 *entry_ids = town_enabled_entry_order;

        entry_id = &entry_ids[next_index];
        do {
            if (*entry_id == 0) {
                entry_id = entry_ids;
                next_index = 0;
            }
            if (func_8001E670(entries[*entry_id].value) != 0) {
                break;
            }
            next_index++;
            entry_id++;
        } while (next_index != start_index);
    }
    town_event_state->entry_index = next_index;
    return town_enabled_entry_order[next_index];
}
