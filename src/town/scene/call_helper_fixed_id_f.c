#include "script_symbols.h"
#include "common.h"

extern s32 func_8001A64C(s32);
/* Calls func_8001A64C with F_bar_pad02 and returns its result. */
s32 call_helper_with_fixed_id_0x118c(void) { return func_8001A64C(F_bar_pad02); }
