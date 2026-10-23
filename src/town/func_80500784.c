#include "common.h"

extern s32 check_result_not_minus_one(s32, s32);
/* Calls return with check_result_not_minus_one(grid_y,grid_x)! = - 1. */
s32 check_result_predicate_success(s32 grid_y, s32 grid_x) { return (check_result_not_minus_one(grid_y, grid_x) != -1); }
