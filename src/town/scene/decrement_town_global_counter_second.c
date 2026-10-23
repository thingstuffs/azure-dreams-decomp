#include "script_symbols.h"
#include "common.h"

extern s32 func_80017684(s32);
/* Calls func_80017684 with F_sbs48_pad00 and returns its result. */
s32 decrement_town_global_counter(void) { return func_80017684(F_sbs48_pad00); }
