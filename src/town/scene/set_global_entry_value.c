#include "common.h"
#include "town/scene.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 scene_current_entry_value;
/* Sets the value stored in D_8001C374. */
void set_global_entry_value(s32 value) {
    scene_current_entry_value = value;
}
