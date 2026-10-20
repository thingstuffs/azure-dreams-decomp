#include "common.h"

extern s32 D_800C3960;
s16 get_cached_or_coordinate_transform_value(void *object, s32 lookup_mode);
void apply_object_setup_and_update(void *object, s32 update_context, s32 setup_context);

// Initialize the object's state and delegate the remaining setup.
void initialize_object_and_update(void *object, s32 update_context, s32 setup_context) {
    *(s8 *)((u8 *)object + 0x15) = 0;
    *(void **)((u8 *)object + 0x50) = &D_800C3960;
    *(s16 *)((u8 *)object + 0x72) = get_cached_or_coordinate_transform_value(object, update_context);
    apply_object_setup_and_update(object, update_context, setup_context);
}
