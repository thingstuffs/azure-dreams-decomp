#include "common.h"
#include "town/scene/data_access.h"
#include "m2c_compat.h"
#include "town.h"

extern M2C_UNK D_80018310;

/* Return a pointer to D_80018310. */
s32 *get_scene_entry_data_e(void) {
    return &D_80018310;
}
