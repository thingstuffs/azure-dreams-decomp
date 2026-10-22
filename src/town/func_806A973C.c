#include "common.h"

extern s32 func_80016760(s32, s32);
s32 has_grid_entry_c(s32 grid_y, s32 grid_x) { return (func_80016760(grid_y, grid_x) != -1); }
