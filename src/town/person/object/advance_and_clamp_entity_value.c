#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"

void add_hex_20000_s_signed_offset_hex_14();                      /* extern */
s16 get_clamped_transform_coordinate();                          /* extern */
void apply_object_setup_and_update(void *, s32, s32);

/* Advance the object's fixed-point value and clamp it when it exceeds the limit. */
void advance_and_clamp_entity_value(s32 context, EntityRec *object, s32 update_data) {
    object->z.v = (s32) (object->z.v + object->flags14);
    if (get_clamped_transform_coordinate(object) < object->z.w.i) {
        object->z.w.i = get_clamped_transform_coordinate(object);
        apply_object_setup_and_update((void *)(context), (s32)(object), update_data);
        return;
    }
    add_hex_20000_s_signed_offset_hex_14(object);
}
