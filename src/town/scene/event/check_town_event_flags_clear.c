#include "common.h"

extern s32 func_800168C4(s32, s32);
/* Calls return with func_800168C4(grid_y,grid_x)! = - 1. */
s32 check_town_event_flags_clear(s32 grid_y, s32 grid_x) { return (func_800168C4(grid_y, grid_x) != -1); }
