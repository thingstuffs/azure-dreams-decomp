#include "common.h"

extern u16 D_80083780[];
extern u16 D_800834B8[];
typedef struct {
    u16 field_0;
    u16 field_2;
    u16 field_4;
    u16 field_6;
} Record;
extern Record D_80100E40[];

/* Fill eight records with the selected values from the two global arrays. */
void func_800AAEFC(void) {
    s32 record_index;
    u16 *primary_values;
    u16 *secondary_values;
    volatile Record *record;

    record_index = 0;
    primary_values = D_80083780;
    secondary_values = D_800834B8;
    record = D_80100E40;
    do {
        record->field_0 = primary_values[1];
        record->field_2 = primary_values[3];
        record->field_4 = primary_values[5];
        record_index++;
        record->field_6 = secondary_values[8];
        record++;
    } while (record_index < 8);
}
