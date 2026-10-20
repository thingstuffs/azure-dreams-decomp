#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

s32 advance_person_lookup_value();                             /* extern */
s32 query_lowered_transform_position();                          /* extern */


/* Set the object value to its base plus the source value minus 76. */
void set_object_value_base_plus(s32 source, EntityRec *object) {
    s32 value_offset;
    s32 base_value;

    base_value = query_lowered_transform_position(object);
    value_offset = advance_person_lookup_value(source);
    value_offset -= 0x4C;
    object->z.w.i = (s16) (base_value + value_offset);
}
