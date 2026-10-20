#include "script_symbols.h"
#include "common.h"

extern s32 check_ready_or_run_followup(s32);
s32 get_shared_threshold_value(void) { return check_ready_or_run_followup(F_sbs36_pad19); }
