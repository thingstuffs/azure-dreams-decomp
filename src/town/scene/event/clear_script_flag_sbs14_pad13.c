#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"

extern s32 clear_script_flag_bit(s32);
/* Calls func_80019458 with F_sbs14_pad13 and returns its result. */
s32 clear_script_flag_sbs14_pad13(void) { return clear_script_flag_bit(F_sbs14_pad13); }
