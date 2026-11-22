/* Four slot object owner. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/engine@3755C, CL:town/func_800B7604, CL:town/func_800B771C. */
#include "town/person/four_slot_object_owner_g00628.h"
#include "town/person.h"
#include "town/shop.h"
#include "shared/object_node.h"

/* Initialize slot data and offsets, then configure the object. */
void initialize_four_slot_object(StorageMenuObject *obj) {
    s32 slot_index;

    for (slot_index = 0; slot_index < 2; slot_index++) {
        obj->parts[slot_index]->handler = item_menu_slot_handler_address;
        obj->parts[slot_index]->position->x = slot_index << 7;
    }

    func_800B3558(obj->data);

    for (slot_index = 2; slot_index < 4; slot_index++) {
        obj->parts[slot_index]->handler = obj->data;
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
void bind_storage_display_object(StorageMenuObject *object, ObjectNodeHeader *owner) {
    object->source_owner = owner;
    object->owner_body = NODE_BODY(owner);
    NODE_HEADER(object)->update_callback = advance_storage_open_ramp;
}

/*
 * Sets the owner base value and data pointer, binds three embedded blocks at offsets
 * 0x4C/0x24/0x34, and initializes its four-slot object.
 */
void initialize_four_slot_object_owner(StorageMenuObject *object, ObjectNodeHeader *owner) {
    bind_storage_display_object(object, owner);
    initialize_storage_display_links(&object->links, &object->display, &object->position);
    initialize_four_slot_object(object);
}
