#include "common.h"
#include "town/scene/data_access.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800170B0;

/* Returns the address of D_800170B0. */
s32 *get_scene_entry_data_b(void) {
    return &D_800170B0;
}
