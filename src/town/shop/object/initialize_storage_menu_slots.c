#include "common.h"
#include "town.h"
#include "town/menu.h"
#include "town/shop.h"
#include "town/shop/object.h"
#include "town/data.h"

extern void func_800B3558(void *ptr);
extern void func_800B2F88(void *ptr);
extern void func_800B331C(void *ptr);
extern void arrange_ten_objects_in_columns(void *objects);

/* Initialize slot data pointers and offsets, then set up the object. */
void initialize_storage_menu_slots(AlternateStorageOwner *object) {
    s32 slot_index;

    for (slot_index = 0; slot_index < 2; slot_index++) {
        object->parts[slot_index]->handler = item_menu_slot_handler_address;
        object->parts[slot_index]->position->x = slot_index << 7;
    }

    func_800B3558(object->panel);

    for (slot_index = 2; slot_index < 4; slot_index++) {
        object->parts[slot_index]->handler = object->panel;
        object->parts[slot_index]->position->x = (slot_index - 2) << 7;
    }

    place_item_menu_cursor_parts(object);
    func_800B2F88(&object->parts[6]);
    arrange_storage_item_columns(&object->parts[16]);
    func_800B331C(object->parts);
    arrange_ten_objects_in_columns(&object->parts[26]);
    apply_linked_record_defaults(object);
    update_paged_menu_record(object);
}
