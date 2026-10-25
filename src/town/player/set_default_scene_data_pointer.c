#include "common.h"
#include "town/player.h"

extern s32 scene_idle_callback_address;

/* Sets the output pointer to D_80090A6C. */
void set_default_scene_data_pointer(s32 **out_ptr, void *unused_position, s32 unused_context) {
    *out_ptr = &scene_idle_callback_address;
}
