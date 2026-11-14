#include "common.h"
#include "town.h"

extern s32 find_entry_index_by_grid_bytes(s32, s32); /* Unprototyped: retail call passes more arguments than the callee reads */
/* Calls return with set_script_flag_sbs14_pad22(grid_y,grid_x)! = - 1. */
s32 check_event_dispatch_success(s32 grid_y, s32 grid_x) { return (find_entry_index_by_grid_bytes(grid_y, grid_x) != -1); }
