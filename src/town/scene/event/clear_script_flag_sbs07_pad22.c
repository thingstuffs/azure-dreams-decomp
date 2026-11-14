#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"

extern s32 clear_script_flag_bit(s32);
/* Calls func_800188CC with F_sbs07_pad22 and returns its result. */
s32 clear_script_flag_sbs07_pad22(void) { return clear_script_flag_bit(F_sbs07_pad22); }
