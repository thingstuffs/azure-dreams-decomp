#include "common.h"

#include "engine/effect.h"
#include "engine/runtime.h"
#include "slus/data.h"

extern s32 cache_event_handle_value_and_get_id(s32, s32, s32, s32, s32);

/* Initializes items using the selected table row, then activates and updates the state. */
s32 create_animated_selection_menu_entries(AnimatedSelectionMenuBody *state) {
    s32 item_result;
    s32 item_index;
    u8 position;
    u8 *table;
    u8 *row;

    item_index = 0;
    if (state->count > 0) {
        table = selection_menu_animation_keys;

        do {
            row = (u8 *)((u32)(state->selected_index * 3) + (u32)table);
            position = row[item_index];
            item_result = cache_event_handle_value_and_get_id(state->entry_ids[item_index], item_index, 0x18,
                                   position * 0xC - 0x40,
                                   position * 0x1E + 0x200);
            *(s32 *)&state->entries[item_index] = item_result;
            if (item_result == 0) {
                return 0;
            }
            item_result = state->count;
            item_index++;
        } while (item_index < item_result);
    }

    state->transition_tick = 1;
    state->transition_frames = 1;
    reorder_selection_menu_entries(state);
    return 1;
}
