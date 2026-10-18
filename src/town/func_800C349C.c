#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 get_current_high_bit_flag(); /* extern */

/* koya_mon_namewin_closechk: check whether the hut monster name window has closed. */
void koya_mon_namewin_closechk(void) {
    get_current_high_bit_flag(0, 0, 0, 0);
}
