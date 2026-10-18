#include "shared/runtime_dispatch.h"
#include "common.h"

void func_80041094(s32 notify_value, s16 state_10, s16 state_12, s16 state_14, s32 state_16);

/* Call the handler with code 0x16 and the global selector with its low bit toggled. */
void request_event_with_toggled_selector(void) {
    func_80041094(0x16, 0, 0, 0, D_80082E60.flags16 ^ 1);
}
