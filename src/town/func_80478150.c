#include "common.h"
#include "town/scene/data_access.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_80019BC4;

/* Set the D_80019BC4 flag. */
void request_scene_rescan_a(void) {
    D_80019BC4 = 1;
}
