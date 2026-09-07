#include "common.h"

typedef struct DungeonSlot {
    s8 pad_00[0x13];
    u8 field_13;
    u8 pad_14[0x54 - 0x14];
} DungeonSlot;

extern DungeonSlot *D_800E3DF0[];
extern void func_800422DC(DungeonSlot *slot, DungeonSlot *other);

/* Resets slot state and updates slots referenced by records of type 0x13. */
void func_800948BC(void)
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
    slot_table = D_800E3DF0;
    record = (u8 *)0x8001024B;
    do {
        if (record[-2] == record_type) {
            slot_index = record[0] & 0x1F;
            linked_slot = slot_table[slot_index];
            if (linked_slot != 0) {
                register u32 slot_base ASM_REG("$2");   /* MATCH pin: retail immediate-load split depends on it */
                slot_base = 0x800102F0;
                func_800422DC((DungeonSlot *)(slot_base + slot_index * 0x54), linked_slot);
            }
        }
        count++;
        record += 4;
    } while (count < 0x14);
}
