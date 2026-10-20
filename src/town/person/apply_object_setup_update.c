#include "common.h"
void apply_object_setup_and_update(void *object, s32 update_context, s32 setup_context);                            /* extern */

/* Forward the object and callback arguments to apply_object_setup_and_update. */
void apply_object_setup_update(void *object, s32 callback_arg_1, s32 callback_arg_2) {
    apply_object_setup_and_update(object, callback_arg_1, callback_arg_2);
}
