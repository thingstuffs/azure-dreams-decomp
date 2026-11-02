#include "script_symbols.h"
#include "common.h"

extern s32 clear_script_flag_bit(s32);
/* Calls func_800176FC with F_sbs48_pad00 and returns its result. */
s32 run_service_callback_zero_x_84_zero(void) { return clear_script_flag_bit(F_sbs48_pad00); }
