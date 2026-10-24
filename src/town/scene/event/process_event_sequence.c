#include "town/player.h"
#include "script_symbols.h"
#include "common.h"

/* Process IDs 0x97F, 0x145B, and 0x11FA in sequence. */
void process_event_sequence(void) {
    set_script_flag_bit(F_sbs34_top);
    set_script_flag_bit(F_selfy_get_tamago);
    set_script_flag_bit(Fp_niko_kenkatyu);
}
