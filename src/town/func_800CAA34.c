#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

s32 townAdvancePersonLookupValue();                             /* extern */
s32 townQueryLoweredTransformPosition();                          /* extern */


/* Set the object value to its base plus the source value minus 76. */
void func_800C8194(s32 source, EntityRec *object) {
    s32 value_offset;
    s32 base_value;

    base_value = townQueryLoweredTransformPosition(object);
    value_offset = townAdvancePersonLookupValue(source);
    value_offset -= 0x4C;
    object->z.w.i = (s16) (base_value + value_offset);
}
