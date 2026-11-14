#include "script_symbols.h"
#include "common.h"

extern s32 clear_script_flag_bit(s32);
/* Calls func_800176FC with F_sbs48_pad01 and returns its result. */
s32 clear_script_flag_sbs48_pad01(void) { return clear_script_flag_bit(F_sbs48_pad01); }
