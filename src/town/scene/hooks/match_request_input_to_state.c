#include "common.h"
#include "town/scene.h"
#include "town/scene/hooks.h"

/* Forward the request value if the initial handler call succeeds. */
s32 match_request_input_to_state(void *request_value) {
    if (match_input_low_bits_to_state(request_value) == 0) {
        return 0;
    }
    return match_input_low_bits_to_state(request_value);
}
