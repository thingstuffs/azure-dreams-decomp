#include "town/player.h"
#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"

/* Calls set_script_flag_bit with ID 0xD83. */
void set_script_flag_tt_pad82(void) {
    set_script_flag_bit(Ftt_pad82);
}
