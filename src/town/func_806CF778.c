#include "common.h"

extern s32 store_run_operation_result(s32, s32);
s32 check_run_operation_result_success(s32 arg0, s32 arg1) { return (store_run_operation_result(arg0, arg1) != -1); }
