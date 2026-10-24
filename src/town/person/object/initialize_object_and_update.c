#include "common.h"

extern s32 person_motion_tag;
#include "town/person/object_setup.h"

// Initialize the object's state and delegate the remaining setup.
void initialize_object_and_update(void *object, void *update_context, void *setup_context) {
    *(s8 *)((u8 *)object + 0x15) = 0;
    *(void **)((u8 *)object + 0x50) = &person_motion_tag;
    *(s16 *)((u8 *)object + 0x72) = get_cached_or_coordinate_transform_value(object, update_context);
    apply_object_setup_and_update(object, update_context, setup_context);
}
