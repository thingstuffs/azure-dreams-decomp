#include "common.h"

extern s32 process_entry_list_in_mode_one(s32, s32);
s32 func_8001682C(s32 arg0, s32 arg1) { return (process_entry_list_in_mode_one(arg0, arg1) != -1); }
