#include "script_symbols.h"
#include "common.h"

extern s32 clear_script_flag_bit(s32);
/* Clears script flag F_bar_pad12 and returns clear_script_flag_bit's result. */
s32 clear_script_flag_bar_pad12(void) { return clear_script_flag_bit(F_bar_pad12); }
