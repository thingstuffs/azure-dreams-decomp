#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"
#include "town/player/state.h"


/* Calls func_800194D8 with ID 0x63A. */
s32 dispatch_event_63_a_through_194_d_8(void) {
    return get_script_flag_mask(F_sbs14_pad22);
}
