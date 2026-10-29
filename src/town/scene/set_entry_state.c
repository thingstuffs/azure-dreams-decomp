#include "script_symbols.h"
#include "common.h"

extern s32 call_helper_with_fixed_id_0x118a(s32); /* Unprototyped: retail call passes more arguments than the callee reads */
/* Calls call_helper_with_fixed_id_0x118a with F_sbs07_pad24 and returns its result. */
s32 set_selected_entry_state_3(void) { return call_helper_with_fixed_id_0x118a(F_sbs07_pad24); }
