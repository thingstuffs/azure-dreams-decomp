#include "script_symbols.h"
#include "common.h"

extern s32 set_script_flag_bit(s32);
/* Sets script flag F_sbs48_pad00 and returns set_script_flag_bit's result. */
s32 set_script_flag_sbs48_pad00(void) { return set_script_flag_bit(F_sbs48_pad00); }
