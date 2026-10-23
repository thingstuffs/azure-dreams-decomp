#include "common.h"
#include "town/scene/data_access.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_800183EC;

/* Sets the value stored in D_800183EC. */
void set_scene_handler_value_f(s32 handler_value) {
    D_800183EC = handler_value;
}
