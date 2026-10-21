#include "shared/runtime_dispatch.h"
#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* Request event 0x17 with the low bit of D_80082E76 toggled. */
void request_event_with_toggled_map_bit(void) {
    request_scene_state_with_parameters(0x17, 0, 0, 0, runtime_dispatch_state.flags16 ^ 1);
}
