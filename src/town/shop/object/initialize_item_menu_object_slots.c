#include "town/shop/item/update_item_menu_record_g01150.h"

extern u8 item_menu_slot_handler_address[];

extern void initialize_item_menu_panel_rectangle(void *record);
extern void layout_item_menu_upper_pair_columns(void *context);
extern void layout_item_menu_lower_item_columns(void *context);
extern void position_item_menu_side_indicators(void *record);
extern void layout_item_menu_lower_pair_columns(void *context);
extern void process_item_menu_selected_entry(void *record);

/* Initialize four object slots with shared or embedded data and paired offsets. */
void initialize_item_menu_object_slots(TownObject *object) {
    TownObject *obj = object;
    s32 slot_index;

    for (slot_index = 0; slot_index < 2; slot_index++) {
        obj->parts[slot_index]->handler = item_menu_slot_handler_address;
        obj->parts[slot_index]->position->x = slot_index << 7;
    }

    initialize_item_menu_panel_rectangle((u8 *)obj + 0x28);

    for (slot_index = 2; slot_index < 4; slot_index++) {
        obj->parts[slot_index]->handler = (u8 *)obj + 0x28;
        obj->parts[slot_index]->position->x = (slot_index - 2) << 7;
    }

    set_item_menu_entry_coordinates(obj);
    layout_item_menu_upper_pair_columns(obj->parts);
    layout_item_menu_lower_item_columns(obj->parts);
    position_item_menu_side_indicators(obj->parts);
    layout_item_menu_lower_pair_columns(obj->parts);
    process_item_menu_selected_entry(obj);
}
