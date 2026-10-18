#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 pass_shared_data_to_window_handler(); /* extern */

/* koya_mon_status_close: close the monster status display. */
void koya_mon_status_close(void) {
    pass_shared_data_to_window_handler(0, 0, 0, 0);
}
