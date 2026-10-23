#include "common.h"
#include "town/scene/data_access.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_800183F0;

/* Set the D_800183F0 flag. */
void request_scene_rescan_e(void) {
    D_800183F0 = 1;
}
