#include "common.h"


#include "town/person/object_setup.h"
#include "town/person/object.h"

// Initialize the object's state and delegate the remaining setup.
void reset_heading_and_update_object(TownObjectRecord *object, ObjectPosition *update_context, SpriteFrameState *setup_context) {
    object->scene_active = 0;
    object->state_callback.as_pm = call_object_callback;
    object->heading = get_cached_or_coordinate_transform_value(object, update_context);
    apply_object_setup_and_update(object, update_context, setup_context);
}
