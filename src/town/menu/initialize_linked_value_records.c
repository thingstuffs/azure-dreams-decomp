#include "common.h"
#include "town/menu.h"
#include "town/menu/catalog_parts.h"

extern s32 menu_initial_value_pairs[];

/* Initialize 14 entries from alternating source values and set their linked halfwords to 0x800. */
void initialize_linked_value_records(void) {
    s32 entry_index;
    s32 *source_values;
    void **entry_slot;
    ItemMenuPart **entry_table;
    s16 initial_value;

    entry_index = 0;
    initial_value = 0x800;
    entry_table = catalog_display_node_slots;
    entry_slot = (void **)(entry_table + 14);
    source_values = menu_initial_value_pairs;
    do {
        *(s32 *)*entry_slot = *source_values;
        source_values += 2;
        entry_index++;
        *((s16 *)*(void **)((u8 *)*entry_slot + 8) + 1) = initial_value;
        entry_slot++;
    } while (entry_index < 14);
}
