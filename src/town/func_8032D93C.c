#include "common.h"
#include "m2c_compat.h"

void apply_target_grid_rectangle();            /* extern */

/* Calls apply_target_grid_rectangle with parameters 0x10 and 7. */
void apply_rectangle_preset_10x7(void) {
    apply_target_grid_rectangle(0x10, 7);
}
