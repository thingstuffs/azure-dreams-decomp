#include "common.h"

extern void card_boot_set_slot_selection_marker(void *ptr, s32 value);
extern void card_boot_clear_slot_selection_marker(void *ptr);
extern void card_boot_set_slot_details_selection(void *ptr, s32 index, s32 value);

/* Update the five entries according to the selected index. */
void card_boot_highlight_selected_load_slot(void *state) {
    void *entry_cursor;
    s32 entry_index;

    for (entry_index = 0; entry_index < 5; entry_index++) {
        entry_cursor = (u8 *)state + entry_index * 4;
        if (entry_index == *(s32 *)((u8 *)state + 0x2C)) {
            card_boot_set_slot_selection_marker(*(void **)((u8 *)entry_cursor + 0xC), 1);
        } else {
            card_boot_clear_slot_selection_marker(*(void **)((u8 *)entry_cursor + 0xC));
        }
    }
    card_boot_set_slot_details_selection(*(void **)((u8 *)state + 4), *(s32 *)((u8 *)state + 0x2C), 3);
}
