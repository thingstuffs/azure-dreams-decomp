#include "common.h"

extern s32 *D_80017B90;

/* Passes the global pointer D_80017B90 by reference to apply_position_offset_pair. */
void apply_global_pointer_deltas_c(void) {
    apply_position_offset_pair(&D_80017B90);
}
