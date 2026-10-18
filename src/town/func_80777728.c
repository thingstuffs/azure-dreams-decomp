#include "common.h"

extern s32 process_ids_zero(s32, s32);
s32 read_current_state_value(s32 arg0, s32 arg1) { return (process_ids_zero(arg0, arg1) != -1); }
