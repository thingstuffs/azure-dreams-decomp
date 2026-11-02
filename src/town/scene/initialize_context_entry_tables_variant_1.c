#include "script_symbols.h"
#include "common.h"

extern s32 set_script_flag_bit(s32); /* Unprototyped: retail call passes more arguments than the callee reads */
/* Calls call_helper_with_fixed_id_0x118a with F_sbs07_pad22 and returns its result. */
s32 initialize_context_entry_tables_variant_1(void) { return set_script_flag_bit(F_sbs07_pad22); }
