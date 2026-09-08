#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

s32 func_800AB030();                             /* extern */
s32 func_800C2AE8();                          /* extern */


/* Set the object value to its base plus the source value minus 76. */
void func_800C8194(s32 source, Rec_D_800E3D7C *object) {
    s32 value_offset;
    s32 base_value;

    base_value = func_800C2AE8(object);
    value_offset = func_800AB030(source);
    value_offset -= 0x4C;
    object->unk_08.at02_s16.v = (s16) (base_value + value_offset);
}
