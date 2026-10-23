#include "common.h"
#include "shared/object_index_slots.h"

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

extern s32 message_motion_type_a;
extern s32 D_800C3438;

/*
 * Installs message_motion_type_a and D_800C3438, stores the four supplied data pointers, and
 * registers the object header in object_index_slots.
 */
void initialize_object_and_register_slot(void *object, s32 slot_index, s32 field_58_value, s32 field_5c_value, s32 field_7c_value,
    s32 field_80_value)
{
    s32 registered_slot;

    ((PointerField *)((u8 *)object - 0x10))->value = &message_motion_type_a;
    ((PointerField *)((u8 *)object + 0x50))->value = &D_800C3438;
    ((WordField *)((u8 *)object + 0x60))->value = slot_index;
    ((WordField *)((u8 *)object + 0x58))->value = field_58_value;
    ((WordField *)((u8 *)object + 0x5C))->value = field_5c_value;
    ((WordField *)((u8 *)object + 0x7C))->value = field_7c_value;
    registered_slot = ((WordField *)((u8 *)object + 0x60))->value;
    ((WordField *)((u8 *)object + 0x80))->value = field_80_value;
    object_index_slots[registered_slot].object = (u8 *)object - 0x20;
}
