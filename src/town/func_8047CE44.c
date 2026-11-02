#include "common.h"
#include "town/scene/data_access.h"
#include "town.h"
#include "town/data.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Stores the supplied value in D_80019BC0. */
void set_scene_handler_value_c(s32 handler_value) {
    scene_stored_handler_value = handler_value;
}
