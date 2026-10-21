/* Person record history (G00592). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AD79C, CL:town/func_800AD7FC, PD:town/engine:80100E40. */
#include "town/person/person_record_history_g00592.h"

/* Fill eight records with the selected values from the two global arrays. */
void fill_person_records(void) {
    s32 record_index;
    ObjectPosition *primary_values;
    u16 *secondary_values;

    record_index = 0;
    primary_values = &D_80083780;
    secondary_values = D_800834B8;
    for (; record_index < 8; record_index++) {
        D_80100E40[record_index].field_0 = ((u16)primary_values->x.w.i);
        D_80100E40[record_index].field_2 = ((u16)primary_values->y.w.i);
        D_80100E40[record_index].field_4 = ((u16)primary_values->z.w.i);
        D_80100E40[record_index].field_6 = secondary_values[8];
    }
}

/* Shifts the eight-record history and stores the current values in the first record. */
void shift_history_and_store_current_values(void)
{
    s32 destination_offset;
    s32 record_index;
    u8 *records;
    TownRecord *destination;
    TownRecord *source;

    record_index = 7;
    records = (u8 *)&D_80100E40;
    while (record_index > 0) {
        destination_offset = record_index * 8;
        source = (TownRecord *)(((record_index - 1) * 8) + (u32)records);
        destination = (TownRecord *)(destination_offset + (u32)records);
        destination->field_0 = source->field_0;
        destination->field_2 = source->field_2;
        destination->field_4 = source->field_4;
        ((TownRecord *)destination)->field_6 = source->field_6;
        record_index--;
    }

    {
        ObjectPosition *current_values;
        TownRecord *newest_record;

        current_values = &D_80083780;
        newest_record = (TownRecord *)&D_80100E40;
        newest_record->field_0 = ((u16)current_values->x.w.i);
        newest_record->field_2 = ((u16)current_values->y.w.i);
        newest_record->field_4 = ((u16)current_values->z.w.i);
        newest_record->field_6 = D_800834C8;
    }
}

/* Copies three halfwords from the selected table entry into the destination. */
void load_record_halfwords_3(void *destination, s32 entry_index) {
    s8 *table_base;
    s8 *entry;

    table_base = (s8 *)&D_80100E40;
    entry = table_base + (entry_index * 8);
    *(u16 *)((s8 *)destination + 2) = *(u16 *)(entry + 0);
    *(u16 *)((s8 *)destination + 6) = *(u16 *)(entry + 2);
    *(u16 *)((s8 *)destination + 10) = *(u16 *)(entry + 4);
}

/* Copy the indexed table entry's 16-bit value into the record. */
void copy_person_table_value(Rec_func_800AB014_arg0 *record, s32 entry_index) {
    s8 *table_base;
    s8 *entry;

    table_base = (s8 *) &D_80100E40;
    entry = table_base + (entry_index * 8);
    record->unk_72.as_u16 = (u16) ((S_800AB014_1 *)entry)->unk_06;
}
