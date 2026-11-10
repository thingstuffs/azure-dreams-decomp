#include "town/player/state.h"
#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Call func_8001E578 with 0x400. */
void trigger_event_resource_400(void) {
    set_script_flag_bit(F_sbs01_pad11);
}
