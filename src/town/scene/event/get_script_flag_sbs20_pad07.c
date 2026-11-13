#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"
#include "m2c_compat.h"
#include "town/player/state.h"


/* Calls initialize_state_two_entries_pointer with ID 0x72D. */
s32 get_script_flag_sbs20_pad07(void) {
    return get_script_flag_mask(F_sbs20_pad07);
}
