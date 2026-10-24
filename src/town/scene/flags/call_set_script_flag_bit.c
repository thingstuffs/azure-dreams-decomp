#include "town/player.h"
#include "script_symbols.h"
#include "common.h"

/* Calls set_script_flag_bit with ID 0xD83. */
void call_set_script_flag_bit(void) {
    set_script_flag_bit(Ftt_pad82);
}
