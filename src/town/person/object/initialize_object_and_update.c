#include "common.h"


#include "town/person/object_setup.h"
#include "town/person/object.h"

// Initialize the object's state and delegate the remaining setup.
void initialize_object_and_update(TownObjectRecord *object, void *update_context, void *setup_context) {
    object->unk_15 = 0;
    object->unk_50.as_pm = call_object_callback;
    object->heading = get_cached_or_coordinate_transform_value(object, update_context);
    apply_object_setup_and_update(object, update_context, setup_context);
}
