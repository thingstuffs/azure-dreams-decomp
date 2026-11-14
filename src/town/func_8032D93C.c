#include "common.h"
#include "m2c_compat.h"

#include "town/scene/grid_queries.h"
#include "town.h"

/* Calls is_position_near_grid_cell with parameters 0x10 and 7. */
u32 is_position_near_fixed_grid_cell(void) {
    return is_position_near_grid_cell(0x10, 7);
}
