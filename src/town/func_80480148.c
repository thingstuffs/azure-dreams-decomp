#include "common.h"
#include "town/scene/data_access.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_8001968C;

/* Returns the address of D_8001968C. */
s32 *get_scene_entry_data_a(void) {
    return &D_8001968C;
}
