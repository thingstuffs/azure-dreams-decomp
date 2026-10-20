#include "common.h"
#include "shared/town_delta_words.h"


/* Passes D_80017B98 to apply_half_step_position_deltas by address. */
void apply_global_delta_record_h(void) {
    apply_half_step_position_deltas(&D_80017B98);
}
