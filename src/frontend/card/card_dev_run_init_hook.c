#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Invoke card_dev_set_object_value. */
void card_dev_run_init_hook(struct S_8001F568_0 *object, s32 value) {
    card_dev_set_object_value(object, value);
}
