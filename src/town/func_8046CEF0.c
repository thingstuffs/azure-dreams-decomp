#include "common.h"
#include "town/scene/data_access.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_8001E964;

/* Sets D_8001E964 to 1. */
void request_scene_rescan_d(void) {
    D_8001E964 = 1;
}
