#include "common.h"

extern s32 *D_80017B90;

/* Passes the address of D_80017B90 to apply_half_step_position_deltas. */
void apply_global_pointer_deltas_b(void) {
    apply_half_step_position_deltas(&D_80017B90);
}
