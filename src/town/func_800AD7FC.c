#include "common.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"

typedef struct {
    u16 field_0;
    u16 field_2;
    u16 field_4;
    u16 field_6;
} TownRecord;

extern s16 D_800834C8;
extern s32 D_80100E40;

/* Shifts the eight-record history and stores the current values in the first record. */
void func_800AAF5C(void)
{
    s32 destination_offset;
    s32 record_index;
    u8 *records;
    volatile TownRecord *destination;
    volatile TownRecord *source;

    record_index = 7;
    records = (u8 *)&D_80100E40;
    loop_0: {
        destination_offset = record_index * 8;
        record_index--;
        source = (TownRecord *)((record_index * 8) + (u32)records);
        destination = (TownRecord *)(destination_offset + (u32)records);
        destination->field_0 = source->field_0;
        destination->field_2 = source->field_2;
        destination->field_4 = source->field_4;
        ((TownRecord *)destination)->field_6 = source->field_6;
    } if (record_index > 0) goto loop_0;

    {
        EntityRec *current_values;
        TownRecord *newest_record;

        current_values = &D_80083780;
        newest_record = (TownRecord *)&D_80100E40;
        newest_record->field_0 = ((u16)current_values->x.w.i);
        newest_record->field_2 = ((u16)current_values->y.w.i);
        newest_record->field_4 = ((u16)current_values->z.w.i);
        newest_record->field_6 = D_800834C8;
    }
}
