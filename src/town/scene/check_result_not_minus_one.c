#include "common.h"

extern s32 try_decrement_state_counter(s32, s32);
s32 check_result_not_minus_one(s32 grid_y, s32 grid_x) { return (try_decrement_state_counter(grid_y, grid_x) != -1); }
