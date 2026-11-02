#include "script_symbols.h"
#include "common.h"

extern s32 set_script_flag_bit(s32);
/* Calls check_ready_or_run_followup with F_sbs36_pad19 and returns its result. */
s32 get_shared_threshold_value(void) { return set_script_flag_bit(F_sbs36_pad19); }
