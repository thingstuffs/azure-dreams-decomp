#include "script_symbols.h"
#include "common.h"
#include "town/player/state.h"
#include "town/scene.h"

/* Calls the setup handler with 0x98F, then forwards the arguments. */
void clear_sbs34_pad15_and_process_entry(s32 value, s32 context) {
    clear_script_flag_bit(F_sbs34_pad15);
    process_checked_entry(value, context);
}
