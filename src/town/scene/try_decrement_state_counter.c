#include "common.h"
#include "town/scene.h"

extern s32 decrement_state_counter(s32, s32);
/* Calls return with decrement_state_counter(grid_y,grid_x)! = - 1. */
s32 try_decrement_state_counter(s32 grid_y, s32 grid_x) { return (decrement_state_counter(grid_y, grid_x) != -1); }
