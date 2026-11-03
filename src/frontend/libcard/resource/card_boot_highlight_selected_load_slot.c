#include "common.h"
#include "frontend/card.h"
#include "frontend/libcard.h"
#include "frontend/libcard/resource.h"

/* Update the five entries according to the selected index. */
void card_boot_highlight_selected_load_slot(CardSaveMenuBody *state) {
    CardSaveMenuBody *menu = state;
    s32 entry_index;

    for (entry_index = 0; entry_index < 5; entry_index++) {
        if (entry_index == menu->selection) {
            card_boot_set_slot_selection_marker(menu->slots[entry_index], 1);
        } else {
            card_boot_clear_slot_selection_marker(menu->slots[entry_index]);
        }
    }
    card_boot_set_slot_details_selection(menu->surface, menu->selection, 3);
}
