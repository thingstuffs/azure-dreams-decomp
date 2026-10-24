#include "common.h"
#include "shared/item_menu.h"

extern u8 item_menu_slot_handler_address[];

extern void initialize_item_menu_panel_rectangle(void *record);
extern void set_item_menu_entry_coordinates(ItemMenuObject *object);
extern void layout_item_menu_upper_pair_columns(ItemMenuPart **parts);
extern void layout_item_menu_lower_item_columns(ItemMenuPart **parts);
extern void position_item_menu_side_indicators(ItemMenuPart **parts);
extern void layout_item_menu_lower_pair_columns(ItemMenuPart **parts);
extern void process_item_menu_selected_entry(ItemMenuObject *object);

/* Initialize four object slots with shared or embedded data and paired offsets. */
void initialize_item_menu_object_slots(ItemMenuObject *object) {
    ItemMenuObject *obj = object;
    s32 slot_index;

    for (slot_index = 0; slot_index < 2; slot_index++) {
        obj->parts[slot_index]->handler = item_menu_slot_handler_address;
        obj->parts[slot_index]->position->x = slot_index << 7;
    }

    initialize_item_menu_panel_rectangle(obj->panel);

    for (slot_index = 2; slot_index < 4; slot_index++) {
        obj->parts[slot_index]->handler = obj->panel;
        obj->parts[slot_index]->position->x = (slot_index - 2) << 7;
    }

    set_item_menu_entry_coordinates(obj);
    layout_item_menu_upper_pair_columns(obj->parts);
    layout_item_menu_lower_item_columns(obj->parts);
    position_item_menu_side_indicators(obj->parts);
    layout_item_menu_lower_pair_columns(obj->parts);
    process_item_menu_selected_entry(obj);
}
