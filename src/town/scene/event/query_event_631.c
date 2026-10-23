#include "script_symbols.h"
#include "common.h"

extern s32 func_80019458(s32);
/* Calls func_80019458 with F_sbs14_pad13 and returns its result. */
s32 query_event_631(void) { return func_80019458(F_sbs14_pad13); }
