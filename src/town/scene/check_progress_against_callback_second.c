#include "script_symbols.h"
#include "common.h"

extern s32 func_8001A5CC(s32);
/* Calls func_8001A5CC with F_bar_pad12 and returns its result. */
s32 check_progress_against_callback(void) { return func_8001A5CC(F_bar_pad12); }
