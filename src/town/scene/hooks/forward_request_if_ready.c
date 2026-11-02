#include "common.h"
#include "town/scene.h"
#include "town/scene/hooks.h"

extern s32 match_input_low_bits_to_state(void *request);

/* Forward the request value if the initial handler call succeeds. */
s32 forward_request_if_ready(void *request_value) {
    if (match_input_low_bits_to_state(request_value) == 0) {
        return 0;
    }
    return match_input_low_bits_to_state(request_value);
}
