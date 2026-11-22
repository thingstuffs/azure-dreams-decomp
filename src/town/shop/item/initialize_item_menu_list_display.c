#include "common.h"
#include "town/shop/item.h"

/* Initialize a list object's configuration, position, and display entries. */
void initialize_item_menu_list_display(ItemMenuTransition *objectData, ObjectNodeHeader *owner, s32 listConfig, s32 entryCount, s32 x, s32 y, u8 *entryIds) {
    initialize_item_menu_record_fields(objectData, owner, listConfig, entryCount, entryIds);
    init_item_menu_list_position(objectData, &objectData->position_links, objectData->position_words, objectData->secondary_words, x, y);
    initialize_item_menu_list_entries(objectData);
}
