#include "common.h"
#include "town.h"

extern s32 find_entry_index_by_grid_bytes(s32, s32); /* Unprototyped: retail call passes a different argument count */
/* Calls return with process_flag_test_record(grid_y,grid_x)! = - 1. */
s32 has_grid_entry(s32 grid_y, s32 grid_x) { return (find_entry_index_by_grid_bytes(grid_y, grid_x) != -1); }
