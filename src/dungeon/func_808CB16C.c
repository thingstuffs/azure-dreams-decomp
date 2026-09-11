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

/* Initialize 14 slots from records, applying part_8 defaults except for the last two slots. */
void func_80123604(void) {
    SlotTable *slot_base;
    register u8 *record_base ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    Slot **slot;
    register Record *record ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 slot_index;
    s32 default_6;
    s32 default_8;

    slot_index = 0;
    default_6 = 0x10;
    default_8 = 0xE0;
    ASM_KEEP(default_6);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(default_8);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    slot_base = &D_80129728;
    ASM_KEEP(slot_base);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    slot = slot_base->slots;
    record_base = D_80120000;
    ASM_KEEP(record_base);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    record = (Record *)(record_base + 0x6A18);
    do {
        (*slot)->part_0 = 0;
        (*slot)->part_4->value_8 = record->value_4;
        (*slot)->part_4->value_A = record->value_6;
        slot_index += 1;
        (*slot)->part_8->value_6 = default_6;
        record += 1;
        (*slot)->part_8->value_8 = default_8;
        slot += 1;
    } while (slot_index < 14);

    {
        SlotTable *slots;
        register u8 *records ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        Slot *current;

        slots = &D_80129728;
        records = D_80120000;
        ASM_KEEP(slots);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        current = slots->slots[12];
        do {
            records += 0x6A18;
        } while (0);
        ASM_KEEP(records);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        current->part_8->value_6 = ((RecordTable *)records)->records[12].value_4;
        slots->slots[12]->part_8->value_8 = ((RecordTable *)records)->records[12].value_6;
        slots->slots[13]->part_8->value_6 = ((RecordTable *)records)->records[13].value_4;
        slots->slots[13]->part_8->value_8 = ((RecordTable *)records)->records[13].value_6;
    }
}
