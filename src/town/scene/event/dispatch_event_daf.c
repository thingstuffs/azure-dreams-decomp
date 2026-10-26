#include "town/player.h"
#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"

/* Invokes set_script_flag_bit with code 0xDAF. */
void dispatch_event_daf(void) {
    set_script_flag_bit(Ftt_pad127);
}
