#include "town/player.h"
#include "script_symbols.h"
#include "common.h"

/* Calls set_script_flag_bit with ID 0xD82. */
void dispatch_event_d_82(void) {
    set_script_flag_bit(Ftt_pad81);
}
