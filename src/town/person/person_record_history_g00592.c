/* Person record history. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AD79C, CL:town/func_800AD7FC, PD:town/engine:80100E40. */
#include "town/person/person_record_history_g00592.h"
#include "town/person.h"

/* Fill eight records with the selected values from the two global arrays. */
void fill_position_history(void) {
    s32 record_index;
    ObjectPosition *primary_values;
    u16 *secondary_values;

    record_index = 0;
    primary_values = &view_reference_entity;
    secondary_values = scene_object_payload_alias;
    for (; record_index < 8; record_index++) {
        town_position_history[record_index].x = primary_values->x.w.i;
        town_position_history[record_index].y = primary_values->y.w.i;
        town_position_history[record_index].z = primary_values->z.w.i;
        town_position_history[record_index].heading = secondary_values[8];
    }
}

/* Shifts the eight-record history and stores the current values in the first record. */
void push_position_history(void)
{
    s32 destination_offset;
    s32 record_index;
    TownPositionHistoryEntry *records;
    TownPositionHistoryEntry *destination;
    TownPositionHistoryEntry *source;

    record_index = 7;
    records = town_position_history;
    while (record_index > 0) {
        destination_offset = record_index * 8;
        source = (TownPositionHistoryEntry *)(((record_index - 1) * 8) + (unsigned long)records);
        destination = (TownPositionHistoryEntry *)(destination_offset + (unsigned long)records);
        destination->x = source->x;
        destination->y = source->y;
        destination->z = source->z;
        destination->heading = source->heading;
        record_index--;
    }

    {
        ObjectPosition *current_values;
        TownPositionHistoryEntry *newest_record;

        current_values = &view_reference_entity;
        newest_record = town_position_history;
        newest_record->x = current_values->x.w.i;
        newest_record->y = current_values->y.w.i;
        newest_record->z = current_values->z.w.i;
        newest_record->heading = D_800834C8;
    }
}

/* Copies three halfwords from the selected table entry into the destination. */
void load_position_history_entry(Fixed1616 *destination, s32 entry_index) {
    TownPositionHistoryEntry *table = town_position_history;
    TownPositionHistoryEntry *entry = table + entry_index;

    destination[0].w.i = entry->x;
    destination[1].w.i = entry->y;
    destination[2].w.i = entry->z;
}

/* Copy the indexed table entry's 16-bit value into the record. */
void copy_history_entry_heading(TownObjectRecord *record, s32 entry_index) {
    record->heading = town_position_history[entry_index].heading;
}
