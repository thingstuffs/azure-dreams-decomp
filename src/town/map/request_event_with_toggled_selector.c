#include "shared/runtime_dispatch.h"
#include "common.h"

void request_scene_state_with_parameters(s32 notify_value, s16 state_10, s16 state_12, s16 state_14, s32 state_16);

/* Call the handler with code 0x16 and the global selector with its low bit toggled. */
void request_event_with_toggled_selector(void) {
    request_scene_state_with_parameters(0x16, 0, 0, 0, runtime_dispatch_state.flags16 ^ 1);
}
