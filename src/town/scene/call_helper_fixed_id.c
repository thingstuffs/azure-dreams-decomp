#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"

extern s32 set_script_flag_bit(s32);
/* Calls func_800193E0 with F_sbs14_pad13 and returns its result. */
s32 call_helper_with_fixed_id_0x631(void) { return set_script_flag_bit(F_sbs14_pad13); }
