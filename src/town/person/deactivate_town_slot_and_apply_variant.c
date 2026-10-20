#include "common.h"
#include "shared/object_index_slots.h"

typedef struct {
    u8 active;
    u8 unk1;
    u8 variant;
    u8 unk3[5];
} TownSlot;

extern u16 D_800D5070[];
extern void install_object_handler_and_clear_slot_flag(void *, void *, void *, void *);

/* Deactivate the town slot, apply its variant to the object and child, and update the object. */
void deactivate_town_slot_and_apply_variant(void *town_object, void *passthru_1, void *passthru_2, void *child)
{
    u32 slot;
    u8 raw_variant;
    ObjectIndexSlot *slot_table;

    slot_table = object_index_slots;
    slot = (u32)(&slot_table[*(s32 *)((u8 *)town_object + 0x60)]);
    raw_variant = ((TownSlot *)slot)->variant;
    ((TownSlot *)slot)->active = 0;
    child = *(void **)((u8 *)town_object + 0x98);
    slot = raw_variant & 3;
    if (child != 0) {
        *(u8 *)((u8 *)child + 4) = slot;
    }
    *(u16 *)((u8 *)town_object + 0x6E) = D_800D5070[slot];
    install_object_handler_and_clear_slot_flag(town_object, passthru_1, passthru_2, child);
}
