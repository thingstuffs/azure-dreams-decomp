#include "common.h"
void apply_object_setup_and_update(void *object, s32 update_context, s32 setup_context);                            /* extern */

/* Forward the object and update arguments to apply_object_setup_and_update. */
void forward_object_setup_arguments(void *object, s32 context, s32 update_data) {
    apply_object_setup_and_update(object, context, update_data);
}
