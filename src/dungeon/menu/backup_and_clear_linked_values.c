#include "common.h"
#include "dungeon/menu.h"
#include "dungeon/data.h"
#include "town/menu/catalog_parts.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Save 12 referenced values to the backup array and clear the originals. */
void backup_and_clear_linked_values(void) {
    ItemMenuPart **table_base;
    ItemMenuPart **value_slot;
    s32 *value_ptr;
    s32 *backup_value;
    s32 value_index;

    value_index = 0x10;
    backup_value = &menu_value_backup;
    table_base = catalog_display_node_slots;
    value_slot = table_base + 16;
    do {
        value_index += 1;
        *backup_value = **(s32 **)value_slot;
        value_ptr = *(s32 **)value_slot;
        value_slot += 1;
        *value_ptr = 0;
        backup_value += 1;
    } while (value_index < 0x1C);
}
