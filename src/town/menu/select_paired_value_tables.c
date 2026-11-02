#include "common.h"
#include "town/menu.h"
#include "town/data.h"

/* Load the selected table value and its paired value into global state. */
void select_paired_value_tables(void *selection) {
    u8 index = ((u8 *)selection)[0x16];

    selected_menu_value = menu_paired_values[index];
    menu_alternate_value_table = menu_paired_values[((u8 *)selection)[0x16] ^ 1];
}
