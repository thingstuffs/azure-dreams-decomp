#include "script_symbols.h"
#include "common.h"

extern s32 func_800176FC(s32);
/* Calls func_800176FC with F_sbs48_pad00 and returns its result. */
s32 run_service_callback_zero_x_84_zero(void) { return func_800176FC(F_sbs48_pad00); }
