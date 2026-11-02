#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"
#include "town/player/state.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Calls func_8001860C with 0x998 and returns zero. */
s32 call_event_998_and_return_zero(void) {
    clear_script_flag_bit(F_sbs34_pad24);
    return 0;
}
