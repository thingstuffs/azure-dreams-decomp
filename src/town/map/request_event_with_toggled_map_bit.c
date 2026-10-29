#include "slus.h"
#include "shared/runtime_dispatch.h"
#include "common.h"
#include "town/map.h"

/*
 * Requests scene state 0x17 with the low bit of runtime_dispatch_state.flags16 toggled in its
 * final parameter.
 */
void request_event_with_toggled_map_bit(void) {
    request_scene_state_with_parameters(0x17, 0, 0, 0, runtime_dispatch_state.flags16 ^ 1);
}
