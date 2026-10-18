#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void apply_object_setup_and_update(void *, M2C_UNK, M2C_UNK);                            /* extern */

/* Forward the object and callback arguments to apply_object_setup_and_update. */
void func_800C3C5C(void *object, M2C_UNK callback_arg_1, M2C_UNK callback_arg_2) {
    apply_object_setup_and_update(object, callback_arg_1, callback_arg_2);
}
