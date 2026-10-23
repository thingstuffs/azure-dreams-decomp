#include "script_symbols.h"
#include "common.h"

extern s32 func_800188CC(s32);
/* Calls func_800188CC with F_sbs07_pad27 and returns its result. */
s32 check_inputs_after_threshold_five(void) { return func_800188CC(F_sbs07_pad27); }
