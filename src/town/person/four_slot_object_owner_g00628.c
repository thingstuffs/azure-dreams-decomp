/* Four slot object owner (G00628). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/engine@3755C, CL:town/func_800B7604, CL:town/func_800B771C. */
#include "town/person/four_slot_object_owner_g00628.h"
#include "town/person.h"
#include "town/shop.h"
#include "shared/object_node.h"

/* Initialize slot data and offsets, then configure the object. */
void initialize_four_slot_object(StorageDisplayBody *obj) {
    s32 slot_index;

    for (slot_index = 0; slot_index < 2; slot_index++) {
        obj->parts[slot_index]->handler = item_menu_slot_handler_address;
        obj->parts[slot_index]->position->x = slot_index << 7;
    }

    func_800B3558(obj->unk20);

    for (slot_index = 2; slot_index < 4; slot_index++) {
        obj->parts[slot_index]->handler = obj->unk20;
        obj->parts[slot_index]->position->x = (slot_index - 2) << 7;
    }

    func_800B47BC(obj);
    func_800B4908(&obj->parts[6]);
    func_800B49A8(&obj->parts[16]);
    func_800B4A60(obj->parts);
    func_800B474C(&obj->parts[26]);
    initialize_storage_cursor(obj);
    update_storage_display(obj);
}

/* Set the record's data pointer, base value, and value offset by 0x20. */
void set_record_value_and_data_pointer(void *field_ptr, s32 base_value) {
    StorageDisplayBody *object = field_ptr;

    object->unk10 = base_value;
    object->unk00 = (s32)(base_value + 0x20);
    ((ObjectNodeHeader *)field_ptr - 1)->update_callback = &D_800B4C38;
}

/*
 * Sets the owner base value and data pointer, binds three embedded blocks at offsets
 * 0x4C/0x24/0x34, and initializes its four-slot object.
 */
void initialize_four_slot_object_owner(u8 *owner, s32 base_value) {
    set_record_value_and_data_pointer(owner, base_value);
    initialize_storage_display_links(owner + 0x4C, owner + 0x24, owner + 0x34);
    initialize_four_slot_object((struct StorageDisplayBody *)(owner));
}
