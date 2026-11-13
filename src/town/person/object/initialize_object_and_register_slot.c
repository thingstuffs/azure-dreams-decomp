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
    void *value;
} PointerField;

typedef struct {
    s32 value;
} WordField;




/*
 * Installs message_motion_type_a and D_800C3438, stores the four supplied data pointers, and
 * registers the object header in object_index_slots.
 */
void initialize_object_and_register_slot(TownObjectRecord *object, s32 slot_index, void *field_58_value, void *field_5c_value, void *field_7c_value,
    void *field_80_value)
{
    s32 registered_slot;

    ((PointerField *)((u8 *)object - 0x10))->value = update_object_position_or_cleanup;
    object->unk_50.as_pm = initialize_person_object;
    object->slot = slot_index;
    ((PointerField *)((u8 *)object + 0x58))->value = field_58_value;
    ((PointerField *)((u8 *)object + 0x5C))->value = field_5c_value;
    object->unk_7C.as_pps32 = field_7c_value;
    registered_slot = object->slot;
    object->descriptor = field_80_value;
    object_index_slots[registered_slot].object = NODE_HEADER(object);
}
