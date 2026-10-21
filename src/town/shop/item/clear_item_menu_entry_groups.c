#include "common.h"
void flag_optional_object_for_removal(void *object);                         /* extern */

/* Processes and clears the values referenced by two consecutive groups of ten slots. */
void clear_item_menu_entry_groups(s32 slot_table) {
    s32 **first_slot;
    s32 **second_slot;
    s32 first_index;
    s32 second_index;

    first_index = 0x10;
    first_slot = slot_table + 0x40;
    do {
        first_index += 1;
        flag_optional_object_for_removal(**first_slot);
        **first_slot = 0;
        first_slot += 1;
    } while (first_index < 0x1A);
    second_index = 0x1A;
    second_slot = slot_table + 0x68;
    do {
        second_index += 1;
        flag_optional_object_for_removal(**second_slot);
        **second_slot = 0;
        second_slot += 1;
    } while (second_index < 0x24);
}
