#include "common.h"
#include "m2c_compat.h"

s32 func_80019B54(void *, s32);                                /* extern */
M2C_UNK func_8001B168();   /* extern */

/* Process the request and invoke func_8001B168 when the result is nonzero. */
s32 func_8001751C(void *context, s32 request) {
    s32 result;

    result = func_80019B54(context, request);
    if (result != 0) {
        func_8001B168(0xD6E, 3, 2);
    }
    return result;
}
