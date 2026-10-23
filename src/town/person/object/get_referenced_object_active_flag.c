#include "script_symbols.h"
#include "common.h"

extern s32 func_8001A554(s32);
/* Calls func_8001A554 with F_bar_pad12 and returns its result. */
s32 get_referenced_object_active_flag(void) { return func_8001A554(F_bar_pad12); }
