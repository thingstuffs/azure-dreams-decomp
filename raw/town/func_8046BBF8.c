#include "common.h"

typedef struct TownRecord { u8 pad_00; u8 flags; u8 pad_02[2]; u8 value; u8 pad_05[7]; s32 kind; u8 pad_10[4]; } TownRecord;
typedef s32 (*TownIndexFunc)(s32);
typedef struct TownDispatch { u8 pad_00[0x2D4]; TownIndexFunc index; } TownDispatch;
typedef struct TownRoot { u8 pad_00[0x20]; TownDispatch *dispatch; } TownRoot;
void func_8001A188(TownRecord *, s32 *);
s32 func_8001C57C(TownRecord *);
extern TownRoot *D_80016000;
extern s32 *D_80018868[];
extern u8 *D_80018874[];
extern TownRecord *D_80018A18;

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
    if ((D_80018A18->flags & 0xC0) != 0x80) {
        s32 offset = 0;
        TownRecord *record;

        do {
            s32 *copy_source = source + index;
            TownRecord *write_record;
            record = (TownRecord *)((u8 *)D_80018A18 + offset);
            func_8001A188(record, copy_source);
            write_record = (TownRecord *)((u8 *)D_80018A18 + offset);
            write_record->value = values[index];
            offset += sizeof(TownRecord);
            index++;
            record = (TownRecord *)((u8 *)D_80018A18 + offset);
        } while ((((record->flags & 0xC0) ^ 0x80) != 0));
    }
    if ((D_80018A18->flags & 0xC0) != 0x80) {
        s32 offset = 0;
        s32 end_flags;
        TownRecord *state;
        TownRecord *record;

        for (;;) {
            s32 result;
            s32 observed_kind;
            s32 wanted_kind;
            s32 replacement_kind;

            state = D_80018A18;
            record = (TownRecord *)((u8 *)state + offset);
            observed_kind = record->kind;
            if (observed_kind == 11)
                wanted_kind = 11;
            else {
                wanted_kind = 11;
                end_flags = 128;
                goto next_record;
            }
            end_flags = 128;
            result = func_8001C57C(state);
            replacement_kind = wanted_kind - 1;
            if (result != 0) goto done;
            record = (TownRecord *)((u8 *)D_80018A18 + offset);
            record->kind = replacement_kind;
            goto done;
next_record:
            offset += sizeof(TownRecord);
            record = (TownRecord *)((u8 *)state + offset);
            if ((record->flags & 0xC0) == end_flags) break;
        }
    }
done:
    return D_80018A18;
}
