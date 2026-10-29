#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"
#include "town/player/state.h"

#include "town/player/action_initializers.h"                            /* extern */
extern s8 town_action_reset_byte;

/* Clears town_action_reset_byte before initializing the object transform and handler. */
void clear_shared_flag_and_initialize_object(void *state, void *context, void *mode) {
    town_action_reset_byte = 0;
    initialize_object_transform_and_handler(state, context, mode);
}
