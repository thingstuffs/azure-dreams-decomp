/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/item_menu.h"
#include "engine/item.h"
#include "engine/util.h"
#include "town/shop/item.h"

/* Clear both item-row groups, then give up to ten rows (parts 16-25) the labels of the current page's entries. */
void populate_current_item_menu_page(ItemMenuObject *state) {
    s32 conversion_aux;
    ItemMenuPart *output_slot;
    void *entry_value;
    s32 item_data;
    void *label;
    s32 entry_index;
    s32 slot_index;

    slot_index = 0x10;
    clear_item_menu_entry_groups(state->parts);
    entry_index = state->menu->page * 0xA;
    while (slot_index < 0x1A && entry_index < state->menu->count) {
        entry_value = state->menu->entries[entry_index];
        item_data = select_item_data(entry_value, &conversion_aux);
        entry_index += 1;
        label = func_8004DC14(item_data, conversion_aux);
        output_slot = state->parts[slot_index];
        slot_index += 1;
        output_slot->handler = label;
    }
}
