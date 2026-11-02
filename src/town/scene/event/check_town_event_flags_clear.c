#include "common.h"
#include "town/scene.h"

/* Calls return with func_800168C4(grid_y,grid_x)! = - 1. */
s32 check_town_event_flags_clear(s32 grid_y, s32 grid_x) { return (find_entry_index_by_grid_bytes(grid_y, grid_x) != -1); }
