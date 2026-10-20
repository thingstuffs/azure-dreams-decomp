#include "common.h"

extern s32 check_ready_or_run_followup(s32);
s32 get_shared_threshold_value(void) { return check_ready_or_run_followup(0x9e9); }
