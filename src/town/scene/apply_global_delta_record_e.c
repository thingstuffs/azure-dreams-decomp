#include "common.h"
#include "shared/town_delta_words.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Passes D_80017B94 to apply_position_offset_pair. */
void apply_global_delta_record_e(void) {
    apply_position_offset_pair(&D_80017B94);
}
