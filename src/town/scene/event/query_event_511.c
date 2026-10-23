#include "script_symbols.h"
#include "common.h"

extern s32 func_800188CC(s32);
/* Calls func_800188CC with F_sbs07_pad26 and returns its result. */
s32 query_event_511(void) { return func_800188CC(F_sbs07_pad26); }
