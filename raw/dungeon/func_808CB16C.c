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
extern u8 D_80120000[9];

__asm__(".set D_80120000, 0x80120000");

void func_80123604(void) {
    register SlotTable *slot_base ASM_REG("$2");
    register u8 *record_base ASM_REG("$2");
    register Slot **slot ASM_REG("$4");
    register Record *record ASM_REG("$5");
    s32 count;
    register s32 value_6 ASM_REG("$8");
    register s32 value_8 ASM_REG("$7");

    count = 0;
    value_6 = 0x10;
    value_8 = 0xE0;
    ASM_KEEP(value_6);
    ASM_KEEP(value_8);
    slot_base = &D_80129728;
    ASM_KEEP(slot_base);
    slot = slot_base->slots;
    record_base = D_80120000;
    ASM_KEEP(record_base);
    record = (Record *)(record_base + 0x6A18);
    ASM_KEEP(record);
    do {
        (*slot)->part_0 = 0;
        (*slot)->part_4->value_8 = record->value_4;
        (*slot)->part_4->value_A = record->value_6;
        count += 1;
        (*slot)->part_8->value_6 = value_6;
        record += 1;
        (*slot)->part_8->value_8 = value_8;
        slot += 1;
    } while (count < 14);

    {
        register SlotTable *slots ASM_REG("$4");
        register u8 *records ASM_REG("$5");
        Slot *current;

        slots = &D_80129728;
        records = D_80120000;
        ASM_KEEP(slots);
        ASM_KEEP(records);
        current = slots->slots[12];
        ASM_USE(current);
        records += 0x6A18;
        ASM_KEEP(records);
        current->part_8->value_6 = ((RecordTable *)records)->records[12].value_4;
        slots->slots[12]->part_8->value_8 = ((RecordTable *)records)->records[12].value_6;
        slots->slots[13]->part_8->value_6 = ((RecordTable *)records)->records[13].value_4;
        slots->slots[13]->part_8->value_8 = ((RecordTable *)records)->records[13].value_6;
    }
}
