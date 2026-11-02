#include "common.h"

extern s32 person_motion_tag;
#include "town/person/object_setup.h"
#include "town/person/object.h"

// Initialize the object's state and delegate the remaining setup.
void initialize_object_and_update(TownObjectRecord *object, void *update_context, void *setup_context) {
    object->unk_15 = 0;
    object->unk_50.as_pm = &person_motion_tag;
    object->heading.as_s16 = get_cached_or_coordinate_transform_value(object, update_context);
    apply_object_setup_and_update(object, update_context, setup_context);
}
