#include "common.h"
#include "m2c_compat.h"

#include "town/scene/grid_queries.h"

/* Calls apply_target_grid_rectangle with parameters 0x10 and 7. */
u32 apply_rectangle_preset_10x7(void) {
    return apply_target_grid_rectangle(0x10, 7);
}
