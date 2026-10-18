#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 *D_80017B90;
/* Passes the global pointer's address to apply_signed_stat_deltas. */
void apply_global_pointer_deltas_a(void) {
    apply_signed_stat_deltas(&D_80017B90);
}
