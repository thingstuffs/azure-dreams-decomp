#include "common.h"
#include "town/scene/data_access.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800190F0;
extern s32 *D_80019270;

/* Point D_80019270 at D_800190F0. */
void initialize_scene_entry_data_a(void) {
    D_80019270 = &D_800190F0;
}
