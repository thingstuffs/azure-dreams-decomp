#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800170B0;

/* Returns the address of D_800170B0. */
s32 *get_scene_entry_buffer_e(void) {
    return &D_800170B0;
}
