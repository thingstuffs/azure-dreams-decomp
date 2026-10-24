#include "town/player.h"
#include "script_symbols.h"
#include "common.h"

/* Calls clear_script_flag_bit with the value 0xDAF. */
void call_clear_script_flag_bit(void) {
    clear_script_flag_bit(Ftt_pad127);
}
