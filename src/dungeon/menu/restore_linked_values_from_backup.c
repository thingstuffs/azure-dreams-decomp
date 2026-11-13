#include "common.h"
#include "m2c_compat.h"
#include "dungeon/menu.h"
#include "dungeon/data.h"
#include "town/menu/catalog_parts.h"

/* Restore 12 referenced values from the backup array. */
void restore_linked_values_from_backup(void) {
    ItemMenuPart **table_base;
    s32 **value_slot;
    s32 *value_ptr;
    s32 *backup_value;
    s32 value_index;

    value_index = 0x10;
    backup_value = &menu_value_backup;
    table_base = catalog_display_node_slots;
    value_slot = (s32 **)(table_base + 16);
    do {
        value_ptr = *value_slot;
        value_slot++;
        value_index++;
        *value_ptr = *backup_value;
        backup_value++;
    } while (value_index < 0x1C);
}
