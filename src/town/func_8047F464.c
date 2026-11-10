#include "common.h"
#include "m2c_compat.h"
#include "town.h"

extern M2C_UNK D_80017928;

/* Returns the address of D_80017928. */
s32 *get_scene_entry_buffer_f(void) {
    return &D_80017928;
}
