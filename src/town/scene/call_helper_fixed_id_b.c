#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"

extern s32 func_800193E0(s32);
/* Calls func_800193E0 with F_sbs14_pad23 and returns its result. */
s32 call_helper_with_fixed_id_0x63b(void) { return func_800193E0(F_sbs14_pad23); }
