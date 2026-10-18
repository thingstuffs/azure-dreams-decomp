#include "common.h"
#include "m2c_compat.h"

extern s32 D_80090A6C;

/* Sets the output pointer to D_80090A6C. */
void set_default_scene_data_pointer(M2C_UNK **out_ptr) {
    *out_ptr = &D_80090A6C;
}
