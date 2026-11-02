#include "common.h"
#include "town/scene.h"

/* Calls return with func_80016944(grid_y,grid_x)! = - 1. */
s32 init_request_if_flag_1455(s32 grid_y, s32 grid_x) { return (find_entry_index_by_grid_bytes(grid_y, grid_x) != -1); }
