#include "common.h"

extern s32 process_flag_test_record(s32, s32);
s32 func_800166E8(s32 arg0, s32 arg1) { return (process_flag_test_record(arg0, arg1) != -1); }
