#include "common.h"
#include "m2c_compat.h"
#include "shared/item_menu.h"

int get_item_name_with_shared_text_table(void *);
void populate_item_menu_page_entries(ItemMenuPart **parts, ItemMenuObject *object);
extern void update_item_menu_enabled_record(ItemMenuObject *);
void populate_item_menu_lower_entries(ItemMenuObject *);
void populate_current_item_menu_page(ItemMenuObject *);
extern void update_item_menu_page_bounds(ItemMenuObject *);
extern void item_menu_no_op();

/* Runs the record handlers, then processes the selected entry. */
void process_item_menu_selected_entry(ItemMenuObject *record) {
    ItemMenuState *selection;

    update_item_menu_enabled_record(record);
    populate_item_menu_lower_entries(record);
    populate_current_item_menu_page(record);
    update_item_menu_page_bounds(record);
    populate_item_menu_page_entries(record->parts, record);
    item_menu_no_op(record->parts, record);
    selection = record->menu;
    get_item_name_with_shared_text_table(selection->entries[selection->position]);
}
