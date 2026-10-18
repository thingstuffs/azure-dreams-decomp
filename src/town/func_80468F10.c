#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK *D_80017B90;
/* Passes the global pointer's address to apply_signed_stat_deltas. */
void apply_global_pointer_deltas_a(void) {
    apply_signed_stat_deltas(&D_80017B90);
}
