#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_8001E670(s32);
extern s16 D_8001795C;

/* Pass the current value of D_8001795C to func_8001E670. */
void apply_stored_value_1795_c(void) {
    func_8001E670(D_8001795C);
}
