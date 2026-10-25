#include "common.h"
#include "town/player.h"
#include "town/player.h"

/* Sets the output pointer to D_80090A6C. */
void set_default_scene_data_pointer(s32 **out_ptr, void *unused_position, s32 unused_context) {
    *out_ptr = no_op_scene_callback_b;
}
