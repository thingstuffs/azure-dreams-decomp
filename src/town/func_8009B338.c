#include "common.h"
#include "m2c_compat.h"

void initialize_object_transform_and_handler(void *, void *, s32);                            /* extern */
extern s8 D_80082668;

/* Clear D_80082668 and pass the state, context, and mode to initialize_object_transform_and_handler. */
void clear_shared_flag_and_initialize_object(void *state, void *context, s32 mode) {
    D_80082668 = 0;
    initialize_object_transform_and_handler(state, context, mode);
}
