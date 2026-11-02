#include "script_symbols.h"
#include "common.h"

extern s32 set_script_flag_bit(s32);
/* Calls func_80017684 with F_sbs48_pad00 and returns its result. */
s32 decrement_town_global_counter(void) { return set_script_flag_bit(F_sbs48_pad00); }
