#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"
#include "town/person/position.h"

#include "town/person/object_setup.h"
#include "town/player.h"

/* Advance the object's position and stop its movement when it exceeds the limit. */
void advance_object_position(void *context, EntityRec *object, void *finish_arg) {
    object->z.v = (s32) (object->z.v + object->flags14);
    if (query_lowered_transform_position(object) < object->z.w.i) {
        object->z.w.i = query_lowered_transform_position(object);
        object->flags14 = 0;
        apply_object_setup_and_update(context, object, finish_arg);
        return;
    }
    add_hex_20000_s_signed_offset_hex_14(object);
}
