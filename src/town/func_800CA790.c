#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void apply_object_setup_and_update(void *, M2C_UNK, M2C_UNK);                            /* extern */

/* Forward the object and parameters to apply_object_setup_and_update. */
void forward_mother_event_update(void *object, M2C_UNK param_1, M2C_UNK param_2) {
    apply_object_setup_and_update(object, param_1, param_2);
}
