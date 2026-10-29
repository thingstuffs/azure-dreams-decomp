#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"

extern s32 call_helper_with_fixed_id_0x118a(s32);
/* Calls call_helper_with_fixed_id_0x118a with F_sbs07_pad25 and returns its result. */
s32 query_event_510(void) { return call_helper_with_fixed_id_0x118a(F_sbs07_pad25); }
