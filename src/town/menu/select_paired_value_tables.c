#include "common.h"
#include "town/menu.h"
#include "town/menu/catalog.h"
#include "town/data.h"

/* Load the selected table value and its paired value into global state. */
void select_paired_value_tables(CatalogDisplay *selection) {
    u8 index = selection->active_detail_slot;

    selected_menu_value = menu_paired_values[index];
    menu_alternate_value_table = menu_paired_values[selection->active_detail_slot ^ 1];
}
