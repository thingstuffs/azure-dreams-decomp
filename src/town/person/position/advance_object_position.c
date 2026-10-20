#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"

void add_hex_20000_s_signed_offset_hex_14();                      /* extern */
s16 query_lowered_transform_position();                          /* extern */
void apply_object_setup_and_update(void *, s32, s32);        /* extern */

/* extern */

/* Advance the object's position and stop its movement when it exceeds the limit. */
void advance_object_position(s32 context, EntityRec *object, s32 finish_arg) {
    object->z.v = (s32) (object->z.v + object->flags14);
    if (query_lowered_transform_position(object) < object->z.w.i) {
        object->z.w.i = query_lowered_transform_position(object);
        object->flags14 = 0;
        apply_object_setup_and_update((void *)(context), (s32)(object), finish_arg);
        return;
    }
    add_hex_20000_s_signed_offset_hex_14(object);
}
