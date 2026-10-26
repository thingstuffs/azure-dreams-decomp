#include "town/player.h"
#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"

/* Calls set_script_flag_bit with the fixed argument 0xD8A. */
void dispatch_event_d_8_a(void) {
    set_script_flag_bit(Ftt_pad89);
}
