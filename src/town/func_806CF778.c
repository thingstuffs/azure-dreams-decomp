#include "common.h"
#include "town.h"
#include "town/scene.h"

/* Calls return with store_run_operation_result(grid_y,grid_x)! = - 1. */
s32 check_run_operation_result_success(s32 grid_y, s32 grid_x) { return (find_entry_index_by_grid_bytes(grid_y, grid_x) != -1); }
