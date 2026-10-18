#include "common.h"

extern s32 D_80090A6C;

/* Sets the output pointer to D_80090A6C. */
void set_default_scene_data_pointer(s32 **out_ptr) {
    *out_ptr = &D_80090A6C;
}
