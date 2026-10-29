#include "common.h"
#include "town/shop/item.h"

/* Initialize a list object's configuration, position, and display entries. */
void initialize_item_menu_list_display(s32 objectData, s32 owner, s32 listConfig, s32 entryCount, s32 x, s32 y, s32 entryIds) {
    initialize_item_menu_record_fields(objectData, owner, listConfig, entryCount, entryIds);
    initialize_item_menu_linked_record_vectors(objectData, objectData + 0xC8, objectData + 0xA0, objectData + 0xB0, x, y);
    initialize_item_menu_list_entries(objectData);
}
