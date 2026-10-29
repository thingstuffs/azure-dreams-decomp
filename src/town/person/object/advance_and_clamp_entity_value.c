#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"

s32 get_clamped_transform_coordinate(void *object);                          /* extern */
#include "town/person/object_setup.h"
#include "town/player.h"

/* Advance the object's fixed-point value and clamp it when it exceeds the limit. */
void advance_and_clamp_entity_value(void *context, EntityRec *object, void *update_data) {
    s16 limit;

    object->z.v = (s32) (object->z.v + object->flags14);
    limit = get_clamped_transform_coordinate(object);
    if (limit < object->z.w.i) {
        limit = get_clamped_transform_coordinate(object);
        object->z.w.i = limit;
        apply_object_setup_and_update(context, object, update_data);
        return;
    }
    add_hex_20000_s_signed_offset_hex_14(object);
}
