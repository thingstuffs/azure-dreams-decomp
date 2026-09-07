#include "common.h"

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

typedef struct TownDispatch {
    u8 pad_00[0x2D4];
    TownIndexFunc index;
} TownDispatch;

typedef struct TownRoot {
    u8 pad_00[0x20];
    TownDispatch *dispatch;
} TownRoot;

void func_8001A188(TownRecord *, s32 *);
s32 func_8001C57C(TownRecord *);
extern TownRoot *D_80016000;
extern s32 *D_80018868[];
extern u8 *D_80018874[];
extern TownRecord *D_80018A18;

/* Populate town records and conditionally change the first kind-11 record to kind 10. */
TownRecord *func_8001CBF8(void)
{
    s32 index;
    s32 **source_table = D_80018868;
    u8 **value_table = D_80018874;
    s32 *source;
    u8 *values;

    source = source_table[D_80016000->dispatch->index(0)];
    index = 0;
    values = value_table[D_80016000->dispatch->index(index)];
    if ((((volatile TownRecord *)D_80018A18)->flags & 0xC0) != 0x80) {
        register s32 next_addr_or_end;
        u8 value_or_flags;
        s32 record_flags;
        TownRecord *record;

        do {
            s32 *copy_source = source + index;
            TownRecord *write_record;

            record = (TownRecord *)((u8 *)D_80018A18 + (index * sizeof(TownRecord)));
            func_8001A188(record, copy_source);
            write_record = (TownRecord *)((s32)(index * sizeof(TownRecord)) + (s32)D_80018A18);
            value_or_flags = values[index];
            write_record->value = value_or_flags;
            index++;
            next_addr_or_end = (s32)(index * sizeof(TownRecord)) + (s32)D_80018A18;
            value_or_flags = *(volatile u8 *)&((TownRecord *)next_addr_or_end)->flags;
            record_flags = value_or_flags;
            next_addr_or_end = 128;
            record_flags &= 0xC0;
        } while (record_flags != next_addr_or_end);
    }
    if ((((volatile TownRecord *)D_80018A18)->flags & 0xC0) != 0x80) {
        s32 scan_index = 0;
        s32 end_flags;

        for (;;) {
            TownRecord *record = (TownRecord *)((s32)(scan_index * sizeof(TownRecord)) + (s32)D_80018A18);
            if (record->kind == 11) {
                end_flags = 128;
                if (func_8001C57C(D_80018A18) != 0)
                    goto done;
                ((TownRecord *)((s32)(scan_index * sizeof(TownRecord)) + (s32)D_80018A18))->kind = 10;
                goto done;
            } else {
                end_flags = 128;
            }
            scan_index++;
            record = (TownRecord *)((s32)(scan_index * sizeof(TownRecord)) + (s32)D_80018A18);
            if ((record->flags & 0xC0) == end_flags)
                break;
        }
    }
done:
    return D_80018A18;
}
