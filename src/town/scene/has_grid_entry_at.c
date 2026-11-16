#include "common.h"
#include "town/scene.h"

/* Calls return with has_entry_at_grid_position(grid_y,grid_x)! = - 1. */
s32 has_grid_entry_at(s32 grid_y, s32 grid_x) { return (find_entry_index_by_grid_bytes(grid_y, grid_x) != -1); }
