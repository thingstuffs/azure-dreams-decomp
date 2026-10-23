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

extern void initialize_item_menu_panel_rectangle(void *record);
extern void set_item_menu_entry_coordinates(void *object);
extern void layout_item_menu_upper_pair_columns(void *context);
extern void layout_item_menu_lower_item_columns(void *context);
extern void position_item_menu_side_indicators(void *record);
extern void layout_item_menu_lower_pair_columns(void *context);
extern void process_item_menu_selected_entry(void *record);

/* Initialize four object slots with shared or embedded data and paired offsets. */
void initialize_item_menu_object_slots(Obj *object) {
    Obj *obj = object;
    s32 slot_index;

    for (slot_index = 0; slot_index < 2; slot_index++) {
        obj->unk0xA8[slot_index]->unk00 = item_menu_slot_handler_address;
        obj->unk0xA8[slot_index]->unk04->unk08 = slot_index << 7;
    }

    initialize_item_menu_panel_rectangle((u8 *)obj + 0x28);

    for (slot_index = 2; slot_index < 4; slot_index++) {
        obj->unk0xA8[slot_index]->unk00 = (u8 *)obj + 0x28;
        obj->unk0xA8[slot_index]->unk04->unk08 = (slot_index - 2) << 7;
    }

    set_item_menu_entry_coordinates(obj);
    layout_item_menu_upper_pair_columns(obj->unk0xA8);
    layout_item_menu_lower_item_columns(obj->unk0xA8);
    position_item_menu_side_indicators(obj->unk0xA8);
    layout_item_menu_lower_pair_columns(obj->unk0xA8);
    process_item_menu_selected_entry(obj);
}
