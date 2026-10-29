/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "engine/item.h"
#include "shared/item_menu.h"
#include "town/shop/item.h"

/* Gives up to ten rows (parts 26-35) item labels for the entries of the menu's current page. */
void populate_item_menu_page_entries(ItemMenuPart **parts, ItemMenuObject *object) {
    ItemMenuPart **output_slot;
    void *entry_value;
    s32 entry_index;
    s32 slot_index;
    ItemMenuState *menu;

    slot_index = 0x1A;
    output_slot = &parts[26];
    entry_index = object->menu->page * 0xA;
    while (1) {
        menu = object->menu;
        slot_index += 1;
        if (entry_index >= menu->count) {
            break;
        }
        entry_value = menu->entries[entry_index];
        entry_index += 1;
        (*output_slot)->handler = create_item_label(entry_value);
        output_slot += 1;
        if (slot_index >= 0x24) {
            break;
        }
    }
}
