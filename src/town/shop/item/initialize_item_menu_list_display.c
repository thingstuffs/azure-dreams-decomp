#include "common.h"

extern void initialize_item_menu_record_fields(s32 objectData, s32 owner, s32 listConfig, s32 entryCount, s32 entryIds);
extern void initialize_item_menu_linked_record_vectors(s32 objectData, s32 dataC8, s32 dataA0, s32 dataB0, s32 x, s32 y);
extern void initialize_item_menu_list_entries(s32 objectData);

/* Initialize a list object's configuration, position, and display entries. */
void initialize_item_menu_list_display(s32 objectData, s32 owner, s32 listConfig, s32 entryCount, s32 x, s32 y, s32 entryIds) {
    initialize_item_menu_record_fields(objectData, owner, listConfig, entryCount, entryIds);
    initialize_item_menu_linked_record_vectors(objectData, objectData + 0xC8, objectData + 0xA0, objectData + 0xB0, x, y);
    initialize_item_menu_list_entries(objectData);
}
