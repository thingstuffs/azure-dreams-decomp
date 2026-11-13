#include "common.h"
#include "town/menu.h"
#include "town/data.h"
#include "town/menu/catalog_parts.h"

/* Restore saved values to the entries in slots sixteen through twenty-seven. */
void restore_linked_values_from_backup(void) {
    s32 **entry_slot;
    s32 *entry;
    s32 *saved_value;
    s32 slot_index;
    ItemMenuPart **state_base;

    slot_index = 0x10;
    saved_value = &menu_value_backup;
    state_base = catalog_display_node_slots;
    entry_slot = (s32 **)(state_base + 16);
    do {
        entry = *entry_slot;
        entry_slot += 1;
        slot_index += 1;
        *entry = *saved_value;
        saved_value += 1;
    } while (slot_index < 0x1C);
}
