#include "script_symbols.h"
#include "common.h"

extern s32 clear_script_flag_bit(s32);
/* Calls func_800188CC with F_sbs07_pad27 and returns its result. */
s32 check_inputs_after_threshold_five(void) { return clear_script_flag_bit(F_sbs07_pad27); }
