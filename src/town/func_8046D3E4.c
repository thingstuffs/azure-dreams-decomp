#include "common.h"
#include "town/scene/data_access.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_8001E960;

/* Stores the supplied value in D_8001E960. */
void set_scene_handler_value_e(s32 handler_value) {
    D_8001E960 = handler_value;
}
