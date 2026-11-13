#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"

extern s32 clear_script_flag_bit(s32);
/* Clears script flag F_sbs07_pad23 and returns clear_script_flag_bit's result. */
s32 clear_script_flag_sbs07_pad23(void) { return clear_script_flag_bit(F_sbs07_pad23); }
