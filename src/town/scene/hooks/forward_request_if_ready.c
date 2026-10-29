#include "common.h"
#include "town/scene.h"
#include "town/scene/hooks.h"

extern s32 func_8001689C(void *request);

/* Forward the request value if the initial handler call succeeds. */
s32 forward_request_if_ready(void *request_value) {
    if (func_8001689C(request_value) == 0) {
        return 0;
    }
    return func_8001689C(request_value);
}
