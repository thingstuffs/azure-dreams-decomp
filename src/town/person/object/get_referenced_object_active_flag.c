#include "script_symbols.h"
#include "common.h"

extern s32 set_script_flag_bit(s32);
/* Calls func_8001A554 with F_bar_pad12 and returns its result. */
s32 get_referenced_object_active_flag(void) { return set_script_flag_bit(F_bar_pad12); }
