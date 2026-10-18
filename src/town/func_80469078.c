#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80017B98;

/* Passes D_80017B98 to apply_half_step_position_deltas by address. */
void apply_global_delta_record_h(void) {
    apply_half_step_position_deltas(&D_80017B98);
}
