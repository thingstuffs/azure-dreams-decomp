#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_8001B1DC;

/* Returns a pointer to D_8001B1DC. */
s32 *get_scene_entry_buffer_d(void) {
    return &D_8001B1DC;
}
