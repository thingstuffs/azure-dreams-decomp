#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"

extern s32 func_800188CC(s32);
/* Calls func_800188CC with F_sbs07_pad23 and returns its result. */
s32 check_fixed_query_6_nonzero(void) { return func_800188CC(F_sbs07_pad23); }
