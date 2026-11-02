#include "script_symbols.h"
#include "common.h"
#include "town/player/state.h"

/* Calls return with func_80017798(F_sbs18_pad05)! = 0. */
s32 store_supplied_values(void) { return (get_script_flag_mask(F_sbs18_pad05) != 0); }
