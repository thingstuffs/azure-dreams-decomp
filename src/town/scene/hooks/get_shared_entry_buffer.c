#include "common.h"
#include "m2c_compat.h"
#include "town/scene/hooks.h"

extern M2C_UNK D_8001C338;

/* Returns a pointer to D_8001C338. */
s32 *get_shared_entry_buffer(void) {
    return &D_8001C338;
}
