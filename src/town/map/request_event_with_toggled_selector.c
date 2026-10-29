#include "shared/runtime_dispatch.h"
#include "common.h"
#include "slus.h"
#include "town/map.h"

/* Call the handler with code 0x16 and the global selector with its low bit toggled. */
void request_event_with_toggled_selector(void) {
    request_scene_state_with_parameters(0x16, 0, 0, 0, runtime_dispatch_state.flags16 ^ 1);
}
