#include "script_symbols.h"
#include "common.h"

extern s32 set_script_flag_bit(s32); /* Unprototyped: retail call passes more arguments than the callee reads */
/* Sets script flag F_sbs07_pad27 and returns set_script_flag_bit's result. */
s32 set_script_flag_sbs07_pad27(void) { return set_script_flag_bit(F_sbs07_pad27); }
