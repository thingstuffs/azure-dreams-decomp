#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 scene_charge;
/* Returns the current value of D_80019B00. */
s32 get_cached_entry_value(void) {
    return scene_charge;
}
