#include "common.h"
#include "dungeon/player/item.h"
#include "engine/scene.h"

typedef struct DungeonSlot {
    s8 pad_00[0x13];
    u8 field_13;
    u8 pad_14[0x54 - 0x14];
} DungeonSlot;

extern DungeonSlot *familiar_record_slots[];

/* Resets slot state and updates slots referenced by records of type 0x13. */
void snapshot_inventory_familiar_records(void)
{
    DungeonSlot *slot;
    u8 *record;
    register DungeonSlot **slot_table;
    s32 record_type;
    DungeonSlot *linked_slot;
    s32 count;
    u32 slot_index;

    slot = (DungeonSlot *)0x800102F0;
    count = 0x13;
    do {
        slot->field_13 = 0;
        count--;
        slot++;
    } while (count >= 0);

    count = 0;
    record_type = 0x13;
    slot_table = familiar_record_slots;
    record = (u8 *)0x8001024B;
loop_1:
    {
        if (record[-2] == record_type) {
            slot_index = record[0] & 0x1F;
            linked_slot = slot_table[slot_index];
            if (linked_slot != 0) {
                u32 slot_base;
                slot_base = 0x800102F0;
                build_entity_slot_snapshot((DungeonSlot *)(slot_base + slot_index * 0x54), linked_slot);
            }
        }
        count++;
        record += 4;
    }
    if (count < 0x14)
        goto loop_1;
}
