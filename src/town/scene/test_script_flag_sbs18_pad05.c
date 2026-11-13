#include "script_symbols.h"
#include "common.h"
#include "town/player/state.h"

/* Returns whether script flag F_sbs18_pad05 is set. */
s32 test_script_flag_sbs18_pad05(void) { return (get_script_flag_mask(F_sbs18_pad05) != 0); }
