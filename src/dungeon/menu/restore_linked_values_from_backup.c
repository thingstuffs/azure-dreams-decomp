#include "common.h"
#include "m2c_compat.h"

extern s32 *catalog_display_node_slots[98];
extern s32 menu_value_backup;

/* Restore 12 referenced values from the backup array. */
void restore_linked_values_from_backup(void) {
    s32 *table_base;
    s32 **value_slot;
    s32 *value_ptr;
    s32 *backup_value;
    s32 value_index;

    value_index = 0x10;
    backup_value = &menu_value_backup;
    table_base = catalog_display_node_slots;
    value_slot = (s32 **)(table_base + 0x10);
    do {
        value_ptr = *value_slot;
        value_slot++;
        value_index++;
        *value_ptr = *backup_value;
        backup_value++;
    } while (value_index < 0x1C);
}
