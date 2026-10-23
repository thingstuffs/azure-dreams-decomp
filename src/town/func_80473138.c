#include "common.h"
#include "town/scene/data_access.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_8001B324;

/* Sets D_8001B324 to the supplied value. */
void set_scene_handler_value_d(s32 handler_value) {
    D_8001B324 = handler_value;
}
