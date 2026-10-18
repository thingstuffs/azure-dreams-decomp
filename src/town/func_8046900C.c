#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_80017B94;

/* Passes D_80017B94 to apply_position_offset_pair. */
void apply_global_delta_record_e(void) {
    apply_position_offset_pair(&D_80017B94);
}
