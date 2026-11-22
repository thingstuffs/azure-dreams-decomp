#include "frontend/libcard/slot_menu.h"
#include "common.h"
#include "frontend/card.h"
#include "frontend/libcard.h"

extern void func_80024224(ObjectNodeHeader *slot, s32 enabled); /* MAIN at 0x80024224 sets the copy-source marker. */

/* Updates source and selected slot markers across five card entries, then refreshes the slot details. */
void card_boot_refresh_copy_slot_markers(CardSlotMenuState *menu)
{
    s32 index;

    for (index = 0; index < 5; index++) {
        if (index == menu->unk_2C) {
            func_80024224(menu->slots[index], 1);
        } else if (index == menu->unk_28) {
            card_boot_set_slot_selection_marker(menu->slots[index], 1);
        } else {
            card_boot_clear_slot_selection_marker(menu->slots[index]);
        }
    }

    card_boot_set_slot_details_selection(
        menu->slot_details,
        menu->unk_28,
        menu->selected_command
        );
}
