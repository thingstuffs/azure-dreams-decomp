#include "common.h"
#include "shared/town_delta_words.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Pass the global object D_80017B9C to apply_signed_stat_deltas. */
void apply_global_delta_record_j(void) {
    apply_signed_stat_deltas(&D_80017B9C);
}
