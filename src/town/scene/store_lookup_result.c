#include "common.h"
#include "shared/town_dispatch_data.h"
#include "town/scene.h"
#include "town/data.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 sum_flagged_terminated_entries(void *entry, s32 callback_mode);              /* extern */

/* Store the result of calling func_80016B1C on D_80018AE8. */
void store_lookup_result(void) {
    town_stored_amount = sum_flagged_terminated_entries(&D_80018AE8, 0);
}
