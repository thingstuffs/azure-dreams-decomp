#include "script_symbols.h"
#include "common.h"

extern s32 func_800176FC(s32);
/* Calls func_800176FC with F_sbs48_pad01 and returns its result. */
s32 call_helper_with_fixed_id_0xbdb(void) { return func_800176FC(F_sbs48_pad01); }
