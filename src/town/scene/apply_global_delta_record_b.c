#include "common.h"
#include "shared/town_delta_words.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Pass the global data at D_80017B94 to apply_signed_stat_deltas. */
void apply_global_delta_record_b(void) {
    apply_signed_stat_deltas(&D_80017B94);
}
