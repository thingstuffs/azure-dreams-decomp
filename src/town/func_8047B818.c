#include "town/player/state.h"
#include "script_symbols.h"
#include "common.h"
#include "town.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Call func_800197D8 with 0x400. */
void run_event_400(void) {
    set_script_flag_bit(F_sbs01_pad11);
}
