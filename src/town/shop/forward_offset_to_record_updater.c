#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void update_and_finalize_record();                         /* extern */

/* Passes the base plus 0x20 to update_and_finalize_record. */
void forward_offset_to_record_updater(s32 base) {
    update_and_finalize_record(base + 0x20);
}
