#include "common.h"
#include "shared/object_index_slots.h"
#include "town/person.h"
#include "town/data.h"

extern void install_object_handler_and_clear_slot_flag(void *, void *, void *, void *);

/* Deactivate the town slot, apply its variant to the object and child, and update the object. */
void deactivate_town_slot_and_apply_variant(TownObjectRecord *town_object, ObjectPosition *position, SpriteFrameState *sprite)
{
    u32 slot;
    u8 raw_variant;
    ObjectIndexSlot *slot_table;
    ObjectIndexSlot *entry;
    void *child;

    slot_table = object_index_slots;
    entry = &slot_table[town_object->slot];
    raw_variant = entry->unk_02;
    entry->unk_00 = 0;
    child = town_object->unk_98;
    slot = raw_variant & 3;
    if (child != 0) {
        *((u8 *)child + 4) = slot;
    }
    town_object->unk_6E = town_facing_angles[slot];
    install_object_handler_and_clear_slot_flag(town_object, position, sprite, child);
}
