#include "common.h"

extern s32 store_run_operation_result(s32, s32);
s32 check_run_operation_result_success(s32 grid_y, s32 grid_x) { return (store_run_operation_result(grid_y, grid_x) != -1); }
