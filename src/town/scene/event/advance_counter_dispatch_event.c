#include "script_symbols.h"
#include "common.h"

extern s32 set_script_flag_bit(s32); /* Unprototyped: retail call passes more arguments than the callee reads */
/* Calls call_helper_with_fixed_id_0x118a with F_sbs07_pad27 and returns its result. */
s32 advance_counter_and_dispatch_event(void) { return set_script_flag_bit(F_sbs07_pad27); }
