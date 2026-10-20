#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
struct Rec_func_800B2DA0_arg1; void update_and_finalize_record(struct Rec_func_800B2DA0_arg1 *);                         /* extern */

/* Passes the base plus 0x20 to update_and_finalize_record. */
void forward_offset_to_record_updater(s32 base) {
    update_and_finalize_record((struct Rec_func_800B2DA0_arg1 *)(base + 0x20));
}
