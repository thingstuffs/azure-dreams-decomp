#include "script_symbols.h"
#include "common.h"

extern s32 func_8001A5CC(s32);
s32 check_progress_against_callback(void) { return func_8001A5CC(F_bar_pad12); }
