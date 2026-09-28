#include "common.h"
#include "shared/entity_objects.h"

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
    EntityRec *primary_values;
    u16 *secondary_values;
    volatile Record *record;

    record_index = 0;
    primary_values = &D_80083780;
    secondary_values = D_800834B8;
    record = D_80100E40;
    do {
        record->field_0 = ((u16)primary_values->x.w.i);
        record->field_2 = ((u16)primary_values->y.w.i);
        record->field_4 = ((u16)primary_values->z.w.i);
        record_index++;
        record->field_6 = secondary_values[8];
        record++;
    } while (record_index < 8);
}
