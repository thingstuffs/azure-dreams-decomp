#include "town/person.h"
#include "shared/object_node.h"
#include "shared/object_index_slots.h"
#include "town/person/object.h"
#include "town/person/person_object_lifecycle_g00659.h"

typedef struct {
    s32 active;
    void *object;
} ObjectSlot;


typedef struct {
    s32 value;
} WordField;




/*
 * Installs message_motion_type_a and D_800C3438, stores the four supplied data pointers, and
 * registers the object header in object_index_slots.
 */
void register_object_slot_with_tables(TownObjectRecord *object, s32 slot_index, void *field_58_value, void *field_5c_value, void *field_7c_value,
    void *field_80_value)
{
    s32 registered_slot;

    NODE_HEADER(object)->update_callback = update_object_position_or_cleanup;
    object->state_callback.as_pm = initialize_person_object;
    object->slot = slot_index;
    object->state_handlers = field_58_value;
    object->indexed_handlers = field_5c_value;
    object->animation_tables.as_pps32 = field_7c_value;
    registered_slot = object->slot;
    object->descriptor = field_80_value;
    object_index_slots[registered_slot].object = NODE_HEADER(object);
}
