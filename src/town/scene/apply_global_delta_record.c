#include "common.h"
#include "shared/town_delta_words.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Passes D_80017B94 to apply_half_step_position_deltas. */
void apply_global_delta_record_d(void) {
    apply_half_step_position_deltas(&D_80017B94);
}
