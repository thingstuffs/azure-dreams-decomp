#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void apply_object_setup_and_update(void *, M2C_UNK, M2C_UNK);                            /* extern */

/* Forward the object and update arguments to apply_object_setup_and_update. */
void forward_object_setup_arguments(void *object, M2C_UNK context, M2C_UNK update_data) {
    apply_object_setup_and_update(object, context, update_data);
}
