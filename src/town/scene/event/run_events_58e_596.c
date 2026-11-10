#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"
#include "town/player/state.h"


/* Call func_800177C4 for IDs 0x58E and 0x596 in order. */
void run_events_58e_596(void) {
    clear_script_flag_bit(F_sbs10_pad22);
    clear_script_flag_bit(F_sbs10_pad30);
}
