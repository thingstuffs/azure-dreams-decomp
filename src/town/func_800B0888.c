#include "common.h"

typedef struct {
    s32 field_00;
    s32 field_04;
    s32 field_08;
    s32 field_0C;
    s32 field_10;
    s32 field_14;
    s32 field_18;
    s32 field_1C;
    s32 field_20;
} TownRecord;

extern s32 func_800ADFBC(s32);

/* Refresh the entry count, clamp the selection, and update five-entry page indices. */
void func_800ADFE8(TownRecord *record) {
    if (record != 0) {
        if ((record->field_08 = func_800ADFBC(record->field_20)) != 0) {
            record->field_10 = (record->field_08 - 1) / 5;
            if (record->field_04 >= record->field_08) {
                record->field_04 = record->field_08 - 1;
            }
        } else {
            record->field_04 = 0;
            record->field_10 = 0;
        }
        record->field_0C = record->field_04 / 5;
    }
}
