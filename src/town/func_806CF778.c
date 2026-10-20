#include "common.h"

extern s32 store_run_operation_result(s32, s32);
s32 func_80016778(s32 arg0, s32 arg1) { return (store_run_operation_result(arg0, arg1) != -1); }
