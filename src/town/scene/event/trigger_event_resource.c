#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_8001E578(s32, ...);

/* Call func_8001E578 with 0x400. */
void trigger_event_resource_400(void) {
    func_8001E578(F_sbs01_pad11);
}
