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
