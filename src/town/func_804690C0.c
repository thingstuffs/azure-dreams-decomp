#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_80017B9C;

/* Pass the global object D_80017B9C to apply_signed_stat_deltas. */
void apply_global_delta_record_j(void) {
    apply_signed_stat_deltas(&D_80017B9C);
}
