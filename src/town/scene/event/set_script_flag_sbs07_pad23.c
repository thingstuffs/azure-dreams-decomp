#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"

extern s32 set_script_flag_bit(s32); /* Unprototyped: retail call passes more arguments than the callee reads */
/* Calls is_bar_top_flag_set with F_sbs07_pad23 and returns its result. */
s32 set_script_flag_sbs07_pad23(void) { return set_script_flag_bit(F_sbs07_pad23); }
