#include "common.h"

extern s32 *catalog_display_node_slots[];
extern s32 D_801331A0;

/* Save and clear the values referenced by slots sixteen through twenty-seven. */
void backup_and_clear_linked_values(void) {
    s32 **entry_table;
    s32 **entry_slot;
    s32 *entry;
    s32 *saved_value;
    s32 slot_index;

    slot_index = 0x10;
    saved_value = &D_801331A0;
    entry_table = catalog_display_node_slots;
    entry_slot = entry_table + 0x10;
    do {
        slot_index += 1;
        *saved_value = **entry_slot;
        entry = *entry_slot;
        entry_slot += 1;
        *entry = 0;
        saved_value += 1;
    } while (slot_index < 0x1C);
}
