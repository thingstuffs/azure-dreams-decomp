#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* Process IDs 0x97F, 0x145B, and 0x11FA in sequence. */
void process_event_sequence(void) {
    set_script_flag_bit(0x97F);
    set_script_flag_bit(0x145B);
    set_script_flag_bit(0x11FA);
}
