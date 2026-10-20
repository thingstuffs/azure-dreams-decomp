#include "common.h"
#include "shared/town_delta_words.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Pass D_80017B9C to apply_half_step_position_deltas. */
void apply_global_delta_record_l(void) {
    apply_half_step_position_deltas(&D_80017B9C);
}
