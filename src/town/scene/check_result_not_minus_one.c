#include "common.h"
#include "town/scene.h"

/* Calls return with try_decrement_state_counter(grid_y,grid_x)! = - 1. */
s32 check_result_not_minus_one(s32 grid_y, s32 grid_x) { return (try_decrement_state_counter(grid_y, grid_x) != -1); }
