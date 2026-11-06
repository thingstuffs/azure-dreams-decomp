#include "common.h"
#include "town/scene/hooks.h"
#include "town/scene/grid_entry_query.h"

/* Calls return with func_800178C0(grid_y,grid_x)! = - 1. */
s32 is_pair_result_valid_b(s32 grid_y, s32 grid_x) { return (find_entry_index_by_grid_bytes(grid_y, grid_x) != -1); }
