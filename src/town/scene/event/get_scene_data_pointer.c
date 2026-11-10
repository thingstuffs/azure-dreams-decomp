#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_8001CF24;

/* Returns the address of D_8001CF24. */
s32 *get_scene_data_pointer(void) {
    return &D_8001CF24;
}
