#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef struct TownRecord {
    u8 pad_00;
    u8 flags;
    u8 pad_02[2];
    u8 value;
    u8 pad_05[7];
    s32 kind;
    u8 pad_10[4];
} TownRecord;

typedef s32 (*TownIndexFunc)(s32);

void copy_town_record_pair_fields(TownRecord *, s32 *);
s32 apply_stored_value_17974(void);
extern s32 *D_80018868[];
extern u8 *D_80018874[];
extern TownRecord *D_80018A18;

/* Populate town records and conditionally change the first kind-11 record to kind 10. */
TownRecord *populate_records_and_normalize_kind(void)
{
    s32 index;
    s32 **source_table = D_80018868;
    u8 **value_table = D_80018874;
    s32 *source;
    u8 *values;

    source = source_table[D_80016000->unk_20->callback_2D4(0)];
    index = 0;
    values = value_table[D_80016000->unk_20->callback_2D4(index)];
    if (((((TownRecord *)((s32)(index * sizeof(TownRecord)) + (s32)D_80018A18)))->flags & 0xC0) != 0x80) {
        register s32 next_addr_or_end;
        u8 value_or_flags;
        s32 record_flags;
        TownRecord *record;

        do {
            s32 *copy_source = source + index;
            TownRecord *write_record;

            record = (TownRecord *)((u8 *)D_80018A18 + (index * sizeof(TownRecord)));
            copy_town_record_pair_fields(record, copy_source);
            write_record = (TownRecord *)((s32)(index * sizeof(TownRecord)) + (s32)D_80018A18);
            value_or_flags = values[index];
            write_record->value = value_or_flags;
            index++;
            next_addr_or_end = (s32)(index * sizeof(TownRecord)) + (s32)D_80018A18;
            value_or_flags = ((TownRecord *)next_addr_or_end)->flags;
            next_addr_or_end = 128;
            record_flags = value_or_flags;
            record_flags &= 0xC0;
        } while (record_flags != next_addr_or_end);
    }
    if ((((TownRecord *)D_80018A18)->flags & 0xC0) != 0x80) {
        s32 scan_index = 0;
        s32 end_flags;

        for (;;) {
            TownRecord *record = (TownRecord *)((s32)(scan_index * sizeof(TownRecord)) + (s32)D_80018A18);
            if (record->kind == 11) {
                end_flags = 128;
                if (apply_stored_value_17974() != 0)
                    break;
                ((TownRecord *)((s32)(scan_index * sizeof(TownRecord)) + (s32)D_80018A18))->kind = 10;
                break;
            } else {
                end_flags = 128;
            }
            scan_index++;
            record = (TownRecord *)((s32)(scan_index * sizeof(TownRecord)) + (s32)D_80018A18);
            if ((record->flags & 0xC0) == end_flags)
                break;
        }
    }
    return D_80018A18;
}
