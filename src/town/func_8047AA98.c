#include "script_symbols.h"
#include "common.h"
#include "town.h"
#include "town/player/state.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Call func_800198D0 with the fixed argument 0x14. */
void run_event_14(void) {
    get_script_flag_mask(sn_open_sekkyo_end);
}
