#include "common.h"

typedef struct SlotB {
    u8 pad[8];
    s16 unk08;
} SlotB;

typedef struct SlotA {
    void *unk00;
    SlotB *unk04;
} SlotA;

typedef struct Obj {
    u8 pad[0xA8];
    SlotA **unk0xA8;
} Obj;

extern u8 item_menu_slot_handler_address[];

extern void func_800B3558(void *ptr);
extern void position_decimal_digit_parts(void *ptr);
extern void func_800B2F88(void *ptr);
extern void func_800B3108(void *ptr);
extern void func_800B331C(void *ptr);
extern void arrange_ten_objects_in_columns(void *objects);
extern void apply_linked_record_defaults(void *record);
extern void update_and_finalize_record(void *record);

/* Initialize slot data pointers and offsets, then set up the object. */
void initialize_four_slot_object_variant(Obj *object) {
    Obj *obj = object;
    s32 slot_index;

    for (slot_index = 0; slot_index < 2; slot_index++) {
        obj->unk0xA8[slot_index]->unk00 = item_menu_slot_handler_address;
        obj->unk0xA8[slot_index]->unk04->unk08 = slot_index << 7;
    }

    func_800B3558((u8 *)obj + 0x28);

    for (slot_index = 2; slot_index < 4; slot_index++) {
        obj->unk0xA8[slot_index]->unk00 = (u8 *)obj + 0x28;
        obj->unk0xA8[slot_index]->unk04->unk08 = (slot_index - 2) << 7;
    }

    position_decimal_digit_parts(obj);
    func_800B2F88((u8 *)obj->unk0xA8 + 0x18);
    func_800B3108((u8 *)obj->unk0xA8 + 0x40);
    func_800B331C(obj->unk0xA8);
    arrange_ten_objects_in_columns((u8 *)obj->unk0xA8 + 0x68);
    apply_linked_record_defaults(obj);
    update_and_finalize_record(obj);
}
