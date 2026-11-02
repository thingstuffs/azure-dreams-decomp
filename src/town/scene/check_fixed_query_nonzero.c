#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"

extern s32 clear_script_flag_bit(s32);
/* Calls func_800188CC with F_sbs07_pad23 and returns its result. */
s32 check_fixed_query_6_nonzero(void) { return clear_script_flag_bit(F_sbs07_pad23); }
