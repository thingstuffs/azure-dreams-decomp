#include "common.h"

typedef struct {
    u8 pad_0[8];
    u16 value_8;
    u16 value_A;
} SlotPart4;

typedef struct {
    u8 pad_0[6];
    s16 value_6;
    s16 value_8;
} SlotPart8;

typedef struct {
    s32 part_0;
    SlotPart4 *part_4;
    SlotPart8 *part_8;
} Slot;

typedef struct {
    u8 pad_0[0x38];
    Slot *slots[14];
} SlotTable;

typedef struct {
    u8 pad_0[4];
    u16 value_4;
    u16 value_6;
} Record;

typedef struct {
    Record records[14];
} RecordTable;

extern SlotTable catalog_display_node_slots;
extern RecordTable catalog_frame_layout;

/* Initialize 14 slots from records, applying part_8 defaults except for the last two slots. */
void initialize_catalog_slot_records(void) {
    SlotTable *slot_base;
    Slot **slot;
    Record *record;
    s32 slot_index;
    s32 default_6;
    s16 default_8;

    slot_index = 0;
    default_6 = 0x10;
    default_8 = 0xE0;
    slot_base = &catalog_display_node_slots;
    slot = slot_base->slots;
    for (; slot_index < 14; slot_index++) {
        record = &catalog_frame_layout.records[slot_index];
        (*slot)->part_0 = 0;
        (*slot)->part_4->value_8 = record->value_4;
        (*slot)->part_4->value_A = record->value_6;
        (*slot)->part_8->value_6 = default_6;
        (*slot)->part_8->value_8 = default_8;
        slot += 1;
    }

    {
        SlotTable *slots;
        Record *records;
        Slot *current;

        slots = &catalog_display_node_slots;
        records = catalog_frame_layout.records;
        current = slots->slots[12];
        current->part_8->value_6 = records[12].value_4;
        slots->slots[12]->part_8->value_8 = records[12].value_6;
        slots->slots[13]->part_8->value_6 = records[13].value_4;
        slots->slots[13]->part_8->value_8 = records[13].value_6;
    }
}
