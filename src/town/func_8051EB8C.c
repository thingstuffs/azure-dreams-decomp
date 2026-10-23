#include "common.h"
#include "town/scene/data_access.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_8001D2BB;

/* Returns the address of D_8001D2BB. */
s32 *get_scene_entry_data_d(void) {
    return &D_8001D2BB;
}
