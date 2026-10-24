#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
#include "town/person/object_setup.h"

/* Forward the object and two setup contexts to the selector. */
void forward_object_update_values(void *object, void *value_1, void *value_2, s32 value_3) {
    select_object_setup_path(object, value_1, value_2);
}
