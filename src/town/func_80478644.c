#include "common.h"
#include "town/scene/data_access.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 scene_stored_handler_value;

/* Sets the value stored in D_80019BC0. */
void set_scene_handler_value_b(s32 handler_value) {
    scene_stored_handler_value = handler_value;
}
