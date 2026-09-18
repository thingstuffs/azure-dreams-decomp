#include "common.h"

s32 func_80017200(s32, s32);
s32 func_800173CC(s32, s32);
s32 func_80017FEC(void);

/* Dispatches by status, converting the fallback handler result to a boolean. */
s32 func_80016154(s32 handler_arg, s32 handler_param) {
    s32 result;

    if (func_80017FEC() >= 2) {
        return func_80017200(handler_arg, handler_param);
    }
    result = 0;
    if (func_80017FEC() > 0) {
        result = func_800173CC(handler_arg, handler_param) != 0;
    }
    return result;
}
