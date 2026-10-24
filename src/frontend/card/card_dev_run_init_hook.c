#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void func_80406568(struct S_8001F568_0 *object, s32 value);                            /* extern */

/* Invoke func_80406568. */
void card_dev_run_init_hook(struct S_8001F568_0 *object, s32 value) {
    func_80406568(object, value);
}
