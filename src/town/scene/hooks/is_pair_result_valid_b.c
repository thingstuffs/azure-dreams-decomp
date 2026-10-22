#include "common.h"

extern s32 func_800178C0(s32, s32);
s32 is_pair_result_valid_b(s32 grid_y, s32 grid_x) { return (func_800178C0(grid_y, grid_x) != -1); }
