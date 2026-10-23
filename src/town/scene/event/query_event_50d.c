#include "script_symbols.h"
#include "common.h"

extern s32 func_800188CC(s32);
/* Calls func_800188CC with F_sbs07_pad22 and returns its result. */
s32 query_event_50d(void) { return func_800188CC(F_sbs07_pad22); }
