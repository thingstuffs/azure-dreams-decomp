#include "common.h"
#include "shared/object_index_slots.h"
#include "town/person.h"
#include "town/data.h"

typedef struct {
    u8 active;
    u8 unk1;
    u8 variant;
    u8 unk3[5];
} TownSlot;

extern void install_object_handler_and_clear_slot_flag(void *, void *, void *, void *);

/* Deactivate the town slot, apply its variant to the object and child, and update the object. */
void deactivate_town_slot_and_apply_variant(TownObjectRecord *town_object, void *passthru_1, void *passthru_2, void *child)
{
    u32 slot;
    u8 raw_variant;
    ObjectIndexSlot *slot_table;

    slot_table = object_index_slots;
    slot = (u32)(&slot_table[town_object->slot]);
    raw_variant = ((TownSlot *)slot)->variant;
    ((TownSlot *)slot)->active = 0;
    child = *(void **)((u8 *)town_object + 0x98);
    slot = raw_variant & 3;
    if (child != 0) {
        *((u8 *)child + 4) = slot;
    }
    town_object->unk_6E = town_facing_angles[slot];
    install_object_handler_and_clear_slot_flag(town_object, passthru_1, passthru_2, child);
}
