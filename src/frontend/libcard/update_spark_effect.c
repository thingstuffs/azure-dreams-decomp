#include "frontend/libcard/slot_menu.h"
#include "common.h"
#include "frontend/card.h"
#include "frontend/libcard.h"

extern void advance_linked_object_counter(void *object, s32 value); /* Unprototyped: retail call passes a different argument count */

/* Updates source and selected slot markers across five card entries, then refreshes the slot details. */
void update_spark_effect(void *menu_data)
{
    CardSlotMenuState *menu = menu_data;
    s32 index;

    for (index = 0; index < 5; index++) {
        if (index == menu->unk_2C) {
            advance_linked_object_counter(menu->slots[index], 1);
        } else if (index == menu->unk_28) {
            card_boot_set_slot_selection_marker(menu->slots[index], 1);
        } else {
            card_boot_clear_slot_selection_marker(menu->slots[index]);
        }
    }

    card_boot_set_slot_details_selection(
        menu->slot_details,
        menu->unk_28,
        menu->unk_44
        );
}
