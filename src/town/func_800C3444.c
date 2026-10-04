#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_8009E348(); /* extern */

/* koya_mon_status_close: close the monster status display. */
void koya_mon_status_close(void) {
    func_8009E348(0, 0, 0, 0);
}
