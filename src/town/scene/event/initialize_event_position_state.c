#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"
#include "m2c_compat.h"
#include "town/player/state.h"


/* Calls initialize_state_two_entries_pointer with ID 0x72D. */
s32 initialize_event_position_state(void) {
    return get_script_flag_mask(F_sbs20_pad07);
}
