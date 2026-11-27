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
    raw_variant = entry->motion_param;
    entry->motion_id = 0;
    child = town_object->spawn_active;
    slot = raw_variant & 3;
    if (child != 0) {
        *((u8 *)child + 4) = slot;
    }
    town_object->origin_heading = town_facing_angles[slot];
    install_object_handler_and_clear_slot_flag(town_object, position, sprite, child);
}
