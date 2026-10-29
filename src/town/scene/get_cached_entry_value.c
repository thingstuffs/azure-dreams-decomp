#include "common.h"
#include "town/scene.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 scene_charge;
/* Returns the current value of scene_charge. */
s32 get_cached_entry_value(void) {
    return scene_charge;
}
