#include "common.h"

extern s32 func_80016944(s32, s32);
/* Calls return with func_80016944(grid_y,grid_x)! = - 1. */
s32 init_request_if_flag_1455(s32 grid_y, s32 grid_x) { return (func_80016944(grid_y, grid_x) != -1); }
