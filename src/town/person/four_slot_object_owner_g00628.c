/* Four slot object owner (G00628). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/engine@3755C, CL:town/func_800B7604, CL:town/func_800B771C. */
#include "town/person/four_slot_object_owner_g00628.h"

/* Initialize slot data and offsets, then configure the object. */
void initialize_four_slot_object(Obj *obj) {
    s32 slot_index;

    for (slot_index = 0; slot_index < 2; slot_index++) {
        obj->unk5c[slot_index]->unk00 = item_menu_slot_handler_address;
        obj->unk5c[slot_index]->unk04->unk08 = slot_index << 7;
    }

    func_800B3558(obj->unk20);

    for (slot_index = 2; slot_index < 4; slot_index++) {
        obj->unk5c[slot_index]->unk00 = obj->unk20;
        obj->unk5c[slot_index]->unk04->unk08 = (slot_index - 2) << 7;
    }

    func_800B47BC(obj);
    func_800B4908((u8 *)obj->unk5c + 0x18);
    func_800B49A8((u8 *)obj->unk5c + 0x40);
    func_800B4A60(obj->unk5c);
    func_800B474C((u8 *)obj->unk5c + 0x68);
    func_800B48B8(obj);
    func_800B4B7C(obj);
}

/* Set the record's data pointer, base value, and value offset by 0x20. */
void set_record_value_and_data_pointer(void *field_ptr, s32 base_value) {
    ((S_800B4E7C_0 *)((u8 *)field_ptr - 0x10))->unk_20 = base_value;
    ((S_800B4E7C_0 *)((u8 *)field_ptr - 0x10))->unk_10 = (s32) (base_value + 0x20);
    ((S_800B4E7C_0 *)((u8 *)field_ptr - 0x10))->unk_00 = &D_800B4C38;
}

void initialize_four_slot_object_owner(u8 *owner, s32 base_value) {
    set_record_value_and_data_pointer(owner, base_value);
    func_800B4CBC(owner + 0x4C, owner + 0x24, owner + 0x34);
    initialize_four_slot_object((struct Obj *)(owner));
}
