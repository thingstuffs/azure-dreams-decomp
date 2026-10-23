#include "common.h"
#include "town/scene/data_access.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_80019BC0;

/* Stores the supplied value in D_80019BC0. */
void set_scene_handler_value_c(s32 handler_value) {
    D_80019BC0 = handler_value;
}
