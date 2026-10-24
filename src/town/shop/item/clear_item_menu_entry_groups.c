#include "common.h"
void flag_optional_object_for_removal(void *object);                         /* extern */
#include "shared/item_menu.h"

/* Releases and clears the label objects of the two item-row groups (parts 16-25 and 26-35). */
void clear_item_menu_entry_groups(ItemMenuPart **parts) {
    ItemMenuPart **first_slot;
    ItemMenuPart **second_slot;
    s32 first_index;
    s32 second_index;

    first_index = 0x10;
    first_slot = &parts[16];
    do {
        first_index += 1;
        flag_optional_object_for_removal((*first_slot)->handler);
        (*first_slot)->handler = 0;
        first_slot += 1;
    } while (first_index < 0x1A);
    second_index = 0x1A;
    second_slot = &parts[26];
    do {
        second_index += 1;
        flag_optional_object_for_removal((*second_slot)->handler);
        (*second_slot)->handler = 0;
        second_slot += 1;
    } while (second_index < 0x24);
}
