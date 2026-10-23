#include "common.h"

extern s32 func_80016990(s32, s32);
/* Calls return with func_80016990(grid_y,grid_x)! = - 1. */
s32 has_grid_entry_e(s32 grid_y, s32 grid_x) { return (func_80016990(grid_y, grid_x) != -1); }
