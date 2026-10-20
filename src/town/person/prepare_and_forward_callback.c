#include "common.h"
#include "m2c_compat.h"

s32 create_object_from_three_values(s32 *);                     /* extern */
void reset_object_entry_and_brighten();       /* extern */

/* Prepare the context and forward the arguments to the next handler. */
void prepare_and_forward_callback(s32 object, s32 context, s32 callback_arg) {
    create_object_from_three_values((s32 *)(context));
    reset_object_entry_and_brighten(object, context, callback_arg);
}
