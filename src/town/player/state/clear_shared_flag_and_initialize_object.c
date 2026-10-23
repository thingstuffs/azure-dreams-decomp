#include "common.h"
#include "m2c_compat.h"

void initialize_object_transform_and_handler(void *, void *, s32);                            /* extern */
extern s8 town_action_reset_byte;

/* Clears town_action_reset_byte before initializing the object transform and handler. */
void clear_shared_flag_and_initialize_object(void *state, void *context, s32 mode) {
    town_action_reset_byte = 0;
    initialize_object_transform_and_handler(state, context, mode);
}
