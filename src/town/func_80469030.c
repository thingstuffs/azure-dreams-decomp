#include "common.h"
#include "shared/town_delta_words.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Passes the shared data at D_80017B98 to apply_signed_stat_deltas. */
void apply_global_delta_record_f(void) {
    apply_signed_stat_deltas(&D_80017B98);
}
