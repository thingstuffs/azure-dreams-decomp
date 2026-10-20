#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 select_object_setup_path(void *, s32, s32, s32);                            /* extern */

/* Forward the object and three values to select_object_setup_path. */
void forward_object_update_values(void *object, s32 value_1, s32 value_2, s32 value_3) {
    select_object_setup_path(object, value_1, value_2, value_3);
}
