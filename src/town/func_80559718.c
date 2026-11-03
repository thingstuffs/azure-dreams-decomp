#include "common.h"
#include "town.h"
#include "town/scene.h"

/* Calls return with func_8001673C(grid_y,grid_x)! = - 1. */
s32 has_grid_entry_d(s32 grid_y, s32 grid_x) { return (find_entry_index_by_grid_bytes(grid_y, grid_x) != -1); }
