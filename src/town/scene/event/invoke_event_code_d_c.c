#include "town/player.h"
#include "script_symbols.h"
#include "common.h"

/* Passes 0xD77 to set_script_flag_bit. */
void invoke_event_code_d_77(void) {
    set_script_flag_bit(Ftt_pad70);
}
