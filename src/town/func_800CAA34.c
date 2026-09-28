#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

s32 func_800AB030();                             /* extern */
s32 func_800C2AE8();                          /* extern */


/* Set the object value to its base plus the source value minus 76. */
void func_800C8194(s32 source, EntityRec *object) {
    s32 value_offset;
    s32 base_value;

    base_value = func_800C2AE8(object);
    value_offset = func_800AB030(source);
    value_offset -= 0x4C;
    object->z.w.i = (s16) (base_value + value_offset);
}
