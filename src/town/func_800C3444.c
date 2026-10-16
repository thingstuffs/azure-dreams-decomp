#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 townPassSharedDataToWindowHandler(); /* extern */

/* koya_mon_status_close: close the monster status display. */
void koya_mon_status_close(void) {
    townPassSharedDataToWindowHandler(0, 0, 0, 0);
}
