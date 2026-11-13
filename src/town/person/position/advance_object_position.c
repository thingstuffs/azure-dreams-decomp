#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"
#include "town/person/position.h"

#include "town/person/object_setup.h"
#include "town/player.h"
#include "town/person/object.h"

/* Advance the object's position and stop its movement when it exceeds the limit. */
void advance_object_position(TownObjectRecord *context, EntityRec *object, SpriteFrameState *finish_arg) {
    object->z.v = (s32) (object->z.v + object->flags14);
    if (query_lowered_transform_position(object) < object->z.w.i) {
        object->z.w.i = query_lowered_transform_position(object);
        object->flags14 = 0;
        apply_object_setup_and_update(context, object, finish_arg);
        return;
    }
    add_vertical_gravity(object);
}
