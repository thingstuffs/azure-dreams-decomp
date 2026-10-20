#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void func_80406568();                            /* extern */

/* Invoke func_80406568. */
void card_dev_run_init_hook(void) {
    func_80406568();
}
