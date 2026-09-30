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

extern SlotTable D_80129728;
extern RecordTable D_80126A18;

/* Initialize 14 slots from records, applying part_8 defaults except for the last two slots. */
void func_80123604(void) {
    SlotTable *slot_base;
    Slot **slot;
    Record *record;
    s32 slot_index;
    s32 default_6;
    s16 default_8;

    slot_index = 0;
    default_6 = 0x10;
    default_8 = 0xE0;
    slot_base = &D_80129728;
    slot = slot_base->slots;
    for (; slot_index < 14; slot_index++) {
        record = &D_80126A18.records[slot_index];
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

        slots = &D_80129728;
        records = D_80126A18.records;
        current = slots->slots[12];
        current->part_8->value_6 = records[12].value_4;
        slots->slots[12]->part_8->value_8 = records[12].value_6;
        slots->slots[13]->part_8->value_6 = records[13].value_4;
        slots->slots[13]->part_8->value_8 = records[13].value_6;
    }
}
