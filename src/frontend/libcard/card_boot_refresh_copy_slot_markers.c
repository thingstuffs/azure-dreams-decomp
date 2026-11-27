#include "frontend/libcard/slot_menu.h"
#include "common.h"
#include "frontend/card.h"
#include "frontend/libcard.h"

/* Updates source and selected slot markers across five card entries, then refreshes the slot details. */
void card_boot_refresh_copy_slot_markers(CardSlotMenuState *menu)
{
    s32 index;

    for (index = 0; index < 5; index++) {
        if (index == menu->copy_source_slot) {
            card_boot_set_copy_source_marker(menu->slots[index], 1);
        } else if (index == menu->selected_slot) {
            card_boot_set_slot_selection_marker(menu->slots[index], 1);
        } else {
            card_boot_clear_slot_selection_marker(menu->slots[index]);
        }
    }

    card_boot_set_slot_details_selection(
        menu->slot_details,
        menu->selected_slot,
        menu->selected_command
        );
}
