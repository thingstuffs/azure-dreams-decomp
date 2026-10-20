#include "common.h"

extern s32 func_8001689C();

/* Forward the request value if the initial handler call succeeds. */
s32 forward_request_if_ready(s32 request_value) {
    if (func_8001689C() == 0) {
        return 0;
    }
    return func_8001689C(request_value);
}
