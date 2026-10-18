#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_8001E578(s32, ...);

/* Calls func_8001E578 with 0x400. */
void trigger_event_resource_400_again(void) {
    func_8001E578(0x400);
}
